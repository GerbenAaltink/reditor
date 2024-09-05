class Plugin {

    construct new() {
        _data = {}
        _data["interation"] = 0
        this.iteration = 0
        this.x = 0
        this.y = 0
        _debug = null
        previousKey = ""
    }
   
    debug {
        return _debug
    }
    debug=(value){
        _debug = value
        iteration = 0
    }
    document {
        return Editor.getDocument()
    }
    document=(value){
        Editor.setDocument(value)
    }
    documentLength {
        return document.count 
    }
    line {
        return Editor.getLine()
    }
    lineLength {
        return line.count 
    }
    mode {
        return Editor.getMode()
    }
    x {Editor.getCursorX()}
    x=(value){
        _x = value 
    }
 y {Editor.getCursorY()}
    y=(value){
        _y = value 
    }
    xStr{x.toString}
    yStr{y.toString} 
    iteration {_iteration}
    iteration=(value) {
        _iteration = value
    }
    previousKey {
        return _previousKey
    }
    previousKey=(value){
        _previousKey = value 
    }
    iterationStr {iteration.toString}
    documentPos {
        return Editor.getDocumentPos()
    }
    keyPress(key){
        this.debug = key
        if(key == "Ctrl+Esc+C"){
            Editor.exit("Secret Combo Pressed")
        }
        if(mode == "view"){
           if(key == "$"){
         Editor.setCursorX(lineLength)
            }else if(key == "0"){
                Editor.setCursorX(0)
            }else if(key == "g"){
                if(previousKey == "g"){
                    previousKey = ""
                    Editor.setCursorY(0)
                    Editor.setCursorX(0)
                }else{
                    previousKey = "g"
                }

            }else if(key == "d"){
                
                if(previousKey == "d"){
                    var doc = document[1..documentLength - 1]
                     
                    document = doc
                    previousKey = "" 
                }else{
                    previousKey = "d"
                }    
            } else if(previousKey == "r" || key == "r") {
            if(previousKey == "r"){
                    var doc = Editor.getDocument().toString
                    //var chars = doc.split("")
                    //documentPos.toStrin(
                    //var dPos = documentPos
                   // System.print(dPos)
                   // exit(documentPosdocumentPos)
                   //var dpos = documentPos
                   // chars[dpos] = key
                    //var cpy = chars.join("")
                    //var doc2 = "aaaa".split("")
                    debug = documentPos.toString 
                    System.print(documentPos.toString)
                    //document = doc2.join("")
                    previousKey = ""
                }else if(key == "r"){
                    previousKey = "r"
                }
            
            
            }else if(key == "G"){
                while((Editor.moveNext() < documentLength)){

                }
                
                
            }else {
                previousKey = ""
            }
       }

    }
    iterate() {
        if(iteration == 30){
            iteration = 6
        }else{
            iteration = iteration + 1
        }
    }
    footer {
        return _footer
    }
    footer=(value){
        Editor.setFooter(value)
    
    }
    details {
        var returnstr = yStr + ":" + xStr + " - " + iterationStr
        if(debug){
            returnstr = returnstr + "Debug: " + debug 
        }
        return returnstr
    }
    tick(){
        if(iteration > 5){
            this.footer = Editor.getLine()+"|" + details
        }else if(debug != null){
            this.footer = debug
        }
        iterate()
    }

}

var plugin = Plugin.new()

