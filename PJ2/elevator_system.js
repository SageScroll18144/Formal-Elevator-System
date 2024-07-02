// for (var i = 1; i <= 7; i++) {

//   bms.observe('formula', {
//     selector: "#pos" + i,
//     formulas: ["positions(" + i + ")"],
//     trigger: function(origin, res) {
//       origin.attr("xlink:href", res[0].substring(0, 5) + ".png");
//       origin.attr("data-frog", res[0]);
//     }
//   });

//   // bms.executeEvent({
//   //   selector: "#pos" + i,
//   //   events: [{
//   //     name: "Move_right",
//   //     predicate: function(origin) {
//   //       return "x=" + origin.attr("data-frog");
//   //     }
//   //   }, {
//   //     name: "Move_left",
//   //     predicate: function(origin) {
//   //       return "x=" + origin.attr("data-frog");
//   //     }
//   //   }, {
//   //     name: "Hop_right",
//   //     predicate: function(origin) {
//   //       return "x=" + origin.attr("data-frog");
//   //     }
//   //   }, {
//   //     name: "Hop_left",
//   //     predicate: function(origin) {
//   //       return "x=" + origin.attr("data-frog");
//   //     }
//   //   }]
//   // });

// }

for (var i = 1; i <= 8; i++){
  bms.observe('formula', {
    selector: "#btn_red" + i, 
    formulas: ["btn_actions(" + i + ")"],
    trigger: function (origin, values) {
      
      switch (values[0]) {
        case "FALSE":
          origin.attr("xlink:href", "btn_red.png");
          break;
        case "TRUE":
          origin.attr("xlink:href", "btn_green.png");
          break;
      }      
    }
  });

  bms.observe('formula', {
    selector: "#display_floor_id", 
    formulas: ["display_floor(" + i + ")"],
    trigger: function (origin, values) {
      
      if(values[0] == "TRUE") {
        switch (i) {
          case 1:
            origin.attr("xlink:href", "one.png");
            break;
          case 2:
            origin.attr("xlink:href", "two.png");
            break;
          case 3:
            origin.attr("xlink:href", "three.png");
            break;
          case 4:
            origin.attr("xlink:href", "four.png");
            break;
          case 5:
            origin.attr("xlink:href", "five.png");
            break;
          case 6:
            origin.attr("xlink:href", "six.png");
            break;
          case 7:
            origin.attr("xlink:href", "seven.png");
            break;
          case 8:
            origin.attr("xlink:href", "eight.png");
            break;
        }  
      }

          
    }
  });
}