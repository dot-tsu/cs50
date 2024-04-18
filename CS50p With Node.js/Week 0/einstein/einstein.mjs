import readline from "node:readline";

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

rl.question("m: ", (mass) => {
  console.log("E: ", mass * 300000000 ** 2);
  rl.close();
});
