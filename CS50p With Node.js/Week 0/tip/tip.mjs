import readline from "node:readline";

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

function dollarsToFloat(str) {
  return parseFloat(str.replace("$", ""));
}

function percentToFloat(str) {
  return parseFloat("0." + str.replace("%", ""));
}

function main() {
  rl.question("How much was the meal? ", (dollarsInput) => {
    rl.question("What percentage would you like to tip? ", (percentInput) => {
      const dollars = dollarsToFloat(dollarsInput);
      const percent = percentToFloat(percentInput);
      const tip = dollars * percent;
      console.log(`Leave $${tip.toFixed(2)}`);
      rl.close();
    });
  });
}

main();
