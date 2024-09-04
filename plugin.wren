globals["x"] = Editor.getCursorX()
globals["x_str"] = globals["x"].toString
globals["y"] = Editor.getCursorY()
globals["y_str"] = globals["y"].toString
Editor.setFooter(Editor.getLine()+"|" + globals["y_str"] + ":" + globals["x_str"])
