import readline from "node:readline";

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

rl.question(
  "Whats the answer to the great question of Life, the Universe, and Everything? ",
  (answer) => {
    answer = answer.trim().toLowerCase();
    if (
      (answer.includes("forty") && answer.includes("two")) ||
      answer.includes("42")
    ) {
      console.log("Yes");
    } else {
      console.log("No");
    }
    rl.close();
  }
);
