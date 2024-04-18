import readline from "node:readline";

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

rl.on("line", (input) => {
  let string = input.replaceAll(" ", "...");
  console.log(string);
  rl.close();
});
