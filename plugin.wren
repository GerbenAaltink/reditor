// System.print(val)



globals["x"] = Editor.getCursorX()
 globals["x_str"] = globals["x"].toString
        globals["y"] = Editor.getCursorY()
        globals["y_str"] = globals["y"].toString
        if(globals["i"] == null){
            globals["i"] = 0
        }



        if(globals["i"] < 10){
            Editor.setFooter("Editor!!" + globals["i"].toString)
        }else{
            Editor.setFooter(Editor.getLine()+"|" + globals["y_str"] + ":" + globals["x_str"])
        }
        globals["i"] = globals["i"] + 1
        if(globals["i"] == 20){
            globals["i"] = 0
        
        
        
        }




//Plugin.tick()
//koe["dd"]()
        koe["ddz"]  = 55
        //tick()