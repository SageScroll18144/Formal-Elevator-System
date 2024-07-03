for (var i = 1; i <= 8; i++){

  // Botões internos do elevador
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

  // Display 7 segmentos interno do elevador(visor)
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

  // Portas do pavimento
  bms.observe('formula', {
    selector: "#floor" + i, 
    formulas: ["display_floor(" + i + ")"],
    trigger: function (origin, values) {
      if(values[0] == "TRUE") {
        origin.attr("xlink:href", "open_door.png");
      } else {
        origin.attr("xlink:href", "close_door.png");
      }      
    }
  });

  // Display do pavimento(sentido vetorial do elevador)
  bms.observe('formula', {
    selector: "#display_floor_vector" + i, 
    formulas: ["current_direction"],
    trigger: function (origin, values) {
      switch (values[0]) {
        case "up":
          origin.attr("xlink:href", "up.png");
          break;
        case "down":
          origin.attr("xlink:href", "down.png");
          break;
        case "empty":
          origin.attr("xlink:href", "none.png");
          break;
      }       
    }
  });

  // Botões do pavimento: UP
  bms.observe('formula', {
    selector: "#btn_floor" + (2 * i), 
    formulas: ["floor_leds(" + i + ")"],
    trigger: function (origin, values) {
      if(values[0] == "up"){
        origin.attr("xlink:href", "btn_green.png");
      }else {
        origin.attr("xlink:href", "btn_red.png");
      }

    }
  });

  // Botões do pavimento: DOWN
  bms.observe('formula', {
    selector: "#btn_floor" + (2 * i - 1),
    formulas: ["floor_leds(" + i + ")"],
    trigger: function (origin, values) {
      if(values[0] == "down"){
        origin.attr("xlink:href", "btn_green.png");
      }else {
        origin.attr("xlink:href", "btn_red.png");
      }

    }
  });

}