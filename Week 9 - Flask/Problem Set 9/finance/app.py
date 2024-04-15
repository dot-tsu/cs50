import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # Retrieve user's current cash balance
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Retrieve user's stock portfolio
    stocks = db.execute(
        """
        SELECT stock_symbol, SUM(shares) as total_shares
        FROM purchases
        WHERE user_id = ?
        GROUP BY stock_symbol
    """,
        user_id,
    )

    # Initialize total portfolio value with user's cash
    total_portfolio_value = user_cash

    # Update stock information in the portfolio
    for stock in stocks:
        stock_info = lookup(stock["stock_symbol"])
        stock["current_price"] = usd(stock_info["price"])
        stock["total_value"] = stock_info["price"] * stock["total_shares"]
        total_portfolio_value += stock["total_value"]
        stock["total_value"] = usd(stock["total_value"])

    return render_template(
        "index.html",
        stocks=stocks,
        user_cash=usd(user_cash),
        total_portfolio_value=usd(total_portfolio_value),
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        stock_symbol = request.form.get("symbol")
        stock_shares_str = request.form.get("shares")

        try:
            stock_shares = float(stock_shares_str)
            if stock_shares % 1 != 0:
                raise ValueError("Shares must be a whole number.")
        except ValueError:
            return apology("Invalid stock shares. Must be a whole number.", 400)

        stock_shares = int(stock_shares)  # Convert to integer

        if not stock_symbol or not lookup(stock_symbol):
            return apology("Invalid stock symbol.", 400)

        if stock_shares < 1:
            return apology(
                "Invalid stock shares. Must be greater than or equal to 1.", 400
            )

        user_cash = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )[0]["cash"]
        stock_price = lookup(stock_symbol)["price"]

        if stock_price * stock_shares > user_cash:
            return apology("Insufficient funds", 400)

        # Update user cash
        db.execute(
            "UPDATE users SET cash = cash - ? WHERE id = ?",
            stock_price * stock_shares,
            session["user_id"],
        )

        # Buy the stock
        db.execute(
            "INSERT INTO purchases (user_id, stock_symbol, shares, price) VALUES (?, ?, ?, ?)",
            session["user_id"],
            stock_symbol,
            stock_shares,
            stock_price,
        )

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    # Retrieve user's transaction history with price information
    transactions = db.execute(
        """
        SELECT stock_symbol, shares, price, purchase_time
        FROM purchases
        WHERE user_id = ?
        ORDER BY purchase_time DESC
        """,
        user_id,
    )

    # Format the price as currency
    for transaction in transactions:
        transaction["price"] = usd(transaction["price"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        stock_symbol = request.form.get("symbol")
        DATA = lookup(stock_symbol)
        if not DATA:
            return apology("Not a valid symbol", 400)
        return render_template(
            "quoted.html",
            name=DATA["name"],
            price=usd(DATA["price"]),
            symbol=DATA["symbol"],
        )

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # Check for form data and handle registration
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Please provide a username", 400)
        elif not password:
            return apology("Please provide a password", 400)
        elif not confirmation:
            return apology("Please confirm the password", 400)
        elif password != confirmation:
            return apology("Passwords do not match", 400)

        # Query database for existing username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) >= 1:
            return apology("Username already exists", 400)

        # Insert new user into the database
        hashed_password = generate_password_hash(password)
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            hashed_password,
        )

        # Log in the new user
        new_user = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = new_user[0]["id"]
        return redirect("/")

    # Display registration form for GET requests
    else:
        return render_template("registration.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        stock_symbol = request.form.get("symbol")
        stock_shares = int(request.form.get("shares"))

        # Check if stock symbol is valid
        if not stock_symbol or not lookup(stock_symbol):
            return apology("Invalid stock symbol.", 400)

        # Check if stock_shares is valid
        if stock_shares < 1:
            return apology("Invalid stock shares", 400)

        # Get user's available shares for the given stock
        user_shares = db.execute(
            """
            SELECT SUM(shares) as total_shares
            FROM purchases
            WHERE user_id = ? AND stock_symbol = ?
            GROUP BY stock_symbol
            """,
            session["user_id"],
            stock_symbol,
        )

        # Check if user has sufficient shares to sell
        if not user_shares or stock_shares > user_shares[0]["total_shares"]:
            return apology("Insufficient shares", 400)

        # Get stock information
        stock_info = lookup(stock_symbol)
        stock_price = stock_info["price"]

        # Calculate the selling price
        sell_price = stock_price * stock_shares

        # Update user's cash balance
        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?",
            sell_price,
            session["user_id"],
        )

        # Record the sale in the purchases table
        db.execute(
            """
            INSERT INTO purchases (user_id, stock_symbol, shares, price)
            VALUES (?, ?, ?, ?)
            """,
            session["user_id"],
            stock_symbol,
            -stock_shares,  # Use a negative value to represent sold shares
            stock_price,
        )

        return redirect("/")
    else:
        # Retrieve user's stocks for the select dropdown
        user_stocks = db.execute(
            """
            SELECT stock_symbol
            FROM purchases
            WHERE user_id = ?
            GROUP BY stock_symbol
            """,
            session["user_id"],
        )

        # Render the sell template with necessary data
        return render_template("sell.html", user_stocks=user_stocks)
