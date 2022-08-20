#pragma once
#include <QString>




QString LedButtonOn = "QPushButton { "
                      "color: #333;"
                      "border: 2px solid #555;"
                      "border-radius: 14px; "
                      "border-style: outset;"
                      "background: qradialgradient( "
                       "   cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, "
                        "  radius: 1.5, stop: 0 #fff, stop: 1 #00aa00 "
                        "  ); "

                    "  } "

                 " QPushButton:pressed { "
                  "    border-style: inset; "
                      "background: qradialgradient( "
                          "cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1, "
                          "radius: 1.5, stop: 0 #fff, stop: 1 #cbffcd"
                          ");"
                      "} ";








QString LedButtonOff =
        "QPushButton { "
        "color: #333;"
        "border: 2px solid #555;"
        "border-radius: 14px; "
        "border-style: outset;"
        "background: qradialgradient( "
         "   cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, "
          "  radius: 1.5, stop: 0 #fff, stop: 1 #92ff96 "
          "  ); "

      "  } "

   " QPushButton:pressed { "
    "    border-style: inset; "
        "background: qradialgradient( "
            "cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1, "
            "radius: 1.5, stop: 0 #fff, stop: 1 #cbffcd"
            ");"
        "} ";
