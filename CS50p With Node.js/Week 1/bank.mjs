import readline from "node:readline";

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

rl.question("Greeting: ", (greeting) => {
  greeting = greeting.toLowerCase();
  let payment = 100;
  if (greeting === "hello") {
    payment = 0;
  } else if (greeting.startsWith("h")) {
    payment = 20;
  }
  console.log(`$${payment}`);
  rl.close();
});
