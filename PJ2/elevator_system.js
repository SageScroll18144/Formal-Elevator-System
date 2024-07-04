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
    formulas: ["current_floor"],
    trigger: function (origin, values) {
      switch (values[0]) {
        case "1":
          origin.attr("xlink:href", "one.png");
          break;
        case "2":
          origin.attr("xlink:href", "two.png");
          break;
        case "3":
          origin.attr("xlink:href", "three.png");
          break;
        case "4":
          origin.attr("xlink:href", "four.png");
          break;
        case "5":
          origin.attr("xlink:href", "five.png");
          break;
        case "6":
          origin.attr("xlink:href", "six.png");
          break;
        case "7":
          origin.attr("xlink:href", "seven.png");
          break;
        case "8":
          origin.attr("xlink:href", "eight.png");
          break;
      }             
    }
  });

  //função de atualização da porta
  (function(index) {
    function updateDoor(origin, values) {
      if (values[0] === "TRUE" && values[1] === index.toString()) {
        origin.attr("xlink:href", "open_door.png");
      } else {
        origin.attr("xlink:href", "close_door.png");
      }
    }
  
  
    // Portas do pavimento
    bms.observe('formula', {
      selector: "#floor" + i, 
      formulas: ["status_door", "current_floor"],
      trigger: function (origin, values) { 
         updateDoor(origin, values);      
      }
    });
  })(i);

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

  //Botões do pavimento: UP
  bms.observe('formula', {
    selector: "#btn_floor" + (2 * i), 
    formulas: ["floor_leds_up(" + i + ")"], 
    trigger: function (origin, values) {
      console.log("Valor: ", values);
      (function(index) {
          if (index !== 8 && values[0] === "TRUE"){
            origin.attr("xlink:href", "btn_green.png");
          }else {
            origin.attr("xlink:href", "btn_red.png");
          }
        })(i);
    }
  });

   //Botões do pavimento: DOWN
   bms.observe('formula', {
     selector: "#btn_floor" + ((2 * i)-1),
     formulas: ["floor_leds_down(" + i + ")"], 
      trigger: function (origin, values) { 
        console.log("Valor: ", values);
         (function(index){
         if (index !== 1 && values[0] === "TRUE"){
             origin.attr("xlink:href", "btn_green.png");
           }else {
             origin.attr("xlink:href", "btn_red.png");
           }
         })(i)
    }
  });

  // Alarme do reparo
  bms.observe('formula', {
    selector: "#alarm_repair_id", 
    formulas: ["btn_special(btn_alarm)"],
    trigger: function (origin, values) {
      if (values[0] === "TRUE"){
        origin.attr("xlink:href", "alarm_ob_repair_on.png");
      } else {
        origin.attr("xlink:href", "alarm_ob_repair_off.png");
      }
    }
  });

  // Alarme da porta
  bms.observe('formula', {
    selector: "#alarm_door_id", 
    formulas: ["alarm_door"],
    trigger: function (origin, values) {
      if (values[0] === "TRUE"){
        origin.attr("xlink:href", "alarm_door_ob_repair_on.png");
      } else {
        origin.attr("xlink:href", "alarm_door_ob_repair_off.png");
      }
    }
  });

  // Evento: Botão mover
  bms.executeEvent({
    selector: "#move_id",
    events: [
      { name: "move" }
    ]
  });
  
  // Evento: open door
  bms.executeEvent({
    selector: "#open_door_btn",
    events: [
      { name: "elevator_operation_open_door" }
    ]
  });

// Evento: close_door
bms.executeEvent({
  selector: "#close_door_btn",
  events: [
    { name: "elevator_operation_close_door" }
  ]
});

// Evento: Alarme de segurança e report
bms.executeEvent({
  selector: "#alarm_socorro",
  events: [
    { name: "elevator_operation_alarm" }, 
    { name: "elevator_operation_report" }
  ]
});

// Evento: get_call_phone
bms.executeEvent({
  selector: "#phone_id",
  events: [
    { name: "get_phone_call_from_elevator" }
  ]
});

// Evento: Break to repair e repaired
bms.executeEvent({
  selector: "#floor" + i,
  events: [
    { name: "elevator_operation_break_to_repair" },
    { name: "elevator_operation_repaired" }
  ]
});

// Evento: chamada do pavimento terreo
// bms.executeEvent({
//   selector: "#btn_floor2",
//   events: [
//     { name: "ground_floor_call_elevator" },
//     {
//       name: "cancel_floor",
//       predicate: function(origin) {
//         return "num_floor=" + origin.attr("data-frog") + " & direction= " + nr.val();
//       }
//     }
//   ]
// });

// // Evento: chamada do ultimo pavimento 
// bms.executeEvent({
//   selector: "#btn_floor15",
//   events: [
//     { name: "last_floor_call_elevator" },
//     {
//       name: "cancel_floor",
//       predicate: function(origin) {
//         return "num_floor=" + origin.attr("data-frog") + " & direction= " + nr.val();
//       }
//     }
//   ]
// });

// // Evento: chamada intermediaria pavimento
// bms.executeEvent({
//   selector: "#btn_floor" + i,
//   events: [{
//     name: "intermediary_call_elevator",
//     predicate: function(origin) {
//       return "user_orders=" + origin.attr("data-frog");
//     }
//   }, {
//     name: "cancel_floor",
//     predicate: function(origin) {
//       return "num_floor=" + origin.attr("data-frog") + " & direction= " + nr.val();
//     }
//   }]
// });

// Evento: chama interna do display ou cancelamento
bms.executeEvent({
  selector: "#btn_red" + i,
  events: [{
    name: "elevator_operation_request",
    predicate: function(origin) {
      return "user_orders=" + origin.attr("data-frog");
    }
  }, {
    name: "cancel",
    predicate: function(origin) {
      return "num_floor=" + origin.attr("data-frog");
    }
  },
  {name: "elevator_operation_hold_door"}
  ]
});

//Enter elevator 
bms.executeEvent({
  selector: "#enter_id",
  events: [{
    name: "enter_elevator",
    predicate: function(origin) {
      return "weight=" + origin.attr("data-frog");
    }
  }]
});

//Exit elevator 
bms.executeEvent({
  selector: "#exit_id",
  events: [
    { name: "exit_elevator" }
  ]
});

}
