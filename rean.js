const conversionTable = {
  clkwca: "clock",
  "222so": "222",
  333: "333",
  "333ni": "333bf",
  "333oh": "333oh",
  "444wca": "444",
  "444bld": "444bf",
  "555wca": "555",
  "555bld": "555bf",
  "666wca": "666",
  "777wca": "777",
  mgmp: "minx",
  pyrso: "pyram",
  skbso: "skewb",
  sqrs: "sq1",
  "333fm": "333fm",
};
let toolSelect = document.querySelector(
  "#toolsDiv > div:nth-child(1) > span > select:nth-child(2)"
);
toolSelect.appendChild(new Option("PR Viewer", "pr_viewer"));
toolSelect.addEventListener("change", async () => {
  if (toolSelect.value == "pr_viewer") {
    updatePRs();
  }
});
async function updatePRs() {
  let purrs = await getPRs();
  console.log(purrs);
  const customEventOrder = [
    "clock",
    "222",
    "333",
    "444",
    "555",
    "666",
    "777",
    "pyram",
    "skewb",
    "sq1",
    "333bf",
    "444bf",
    "555bf",
    "333fm",
  ];
  const reversedConversionTable = Object.keys(conversionTable).reduce(
    (obj, key) => ({ ...obj, [conversionTable[key]]: key }),
    {}
  );
  let coolDiv = "";
  for (const event of customEventOrder) {
    if (event in purrs) {
      
        const singleBest = purrs[event].single.best / 100;
        const avgBest = purrs[event].average ? purrs[event].average.best / 100 : false;
        if (
          reversedConversionTable[event] ==
          document.querySelector(
            "#scrambleDiv > div.title > nobr:nth-child(1) > select:nth-child(2)"
          ).value
        ) {
          coolDiv =
            `${event}: ${Math.floor(singleBest / 60) > 0 ? `${Math.floor(singleBest / 60)}:` : ""}${(singleBest-Math.floor(singleBest / 60)*60).toFixed(2)} ${avgBest ? ` | ${Math.floor(avgBest / 60) > 0 ? `${Math.floor(avgBest / 60)}:` : ""}${(avgBest-Math.floor(singleBest / 60)*60).toFixed(2)}` : ""}<br>` + coolDiv;
        } else {
          coolDiv += `${event}: ${Math.floor(singleBest / 60) > 0 ? `${Math.floor(singleBest / 60)}:` : ""}${(singleBest-Math.floor(singleBest / 60)*60).toFixed(2)} ${avgBest ? ` | ${Math.floor(avgBest / 60) > 0 ? `${Math.floor(avgBest / 60)}:` : ""}${(avgBest-Math.floor(singleBest / 60)*60).toFixed(2)}` : ""}<br>`;
        }
      
    }
  }

  coolDiv =
    `<h4>Your PRs</h4><p style="text-align: right;text-decoration: underline;">single | average<p>` +
    coolDiv;

  console.log(coolDiv);
  document.querySelector("#toolsDiv > div:nth-child(1) >div").innerHTML =
    coolDiv;
}
// special for browser only testing
async function getPRs() {
  let wcaId = false;
  if (!wcaId || wcaId == "") {
    alert(
      "Please set your WCA ID by clicking the extension icon\nSetting to default: 2009ZEMD01"
    );
    wcaId = "2009ZEMD01";
  }
  // console.log(wcaId)
  let response = await fetch(
    "https://www.worldcubeassociation.org/api/v0/persons/" + wcaId
  );
  let json = await response.json();

  return json.personal_records;
}
