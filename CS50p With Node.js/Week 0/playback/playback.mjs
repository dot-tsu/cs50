import readline from "node:readline";

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

rl.on("line", (input) => {
  console.log(input.replaceAll(" ", "..."));
  rl.close();
});
