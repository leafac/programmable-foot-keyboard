#lang scribble/manual

@title{Programmable Foot Keyboard}
@author{@author+email["Leandro Facchinetti" "me@leafac.com"]}

@emph{A programmable foot keyboard using @hyperlink["https://learn.adafruit.com/introducing-trinket"]{Adafruit’s Trinket}.}

@tabular[#:style 'boxed
         #:sep @hspace[1]
         #:row-properties '(bottom-border)
         `((, @bold{Documentation} , @hyperlink["https://www.leafac.com/software/programmable-foot-keyboard"]{https://www.leafac.com/software/programmable-foot-keyboard})
           (, @bold{License} , @hyperlink["https://gnu.org/licenses/gpl-3.0.txt"]{GNU General Public License Version 3})
           (, @bold{Code of Conduct} , @hyperlink["http://contributor-covenant.org/version/1/4/"]{Contributor Covenant v1.4.0})
           (, @bold{Source} , @hyperlink["https://git.leafac.com/programmable-foot-keyboard"]{https://git.leafac.com/programmable-foot-keyboard})
           (, @bold{Bug Reports} , @para{Write emails to @hyperlink["mailto:programmable-foot-keyboard@leafac.com"]|{programmable-foot-keyboard@leafac.com}|.})
           (, @bold{Contributions} , @para{Send @hyperlink["https://git-scm.com/docs/git-format-patch"]{patches} and @hyperlink["https://git-scm.com/docs/git-request-pull"]{pull requests} via email to @hyperlink["mailto:programmable-foot-keyboard@leafac.com"]|{programmable-foot-keyboard@leafac.com}|.}))]

@section[#:tag "overview"]{Overview}

@image["front.jpg"]

@image["connected.jpg"]

@image["back.jpg"]

@image["inside.jpg"]

Do it yourself programmable foot keyboard. It connects to the computer via USB and acts as a regular keyboard. It is possible to program which keys it sends when pressing the switches. I use it to scroll tabs when playing the guitar, to start and stop recording, as modifiers in text editors (for example, holding Meta and Control in @hyperlink["https://www.gnu.org/software/emacs/"]{Emacs}), and more.

@section[#:tag "shopping-list"]{Shopping List}

The total cost of the project is around $10:

@itemlist[
 @item{@bold{@hyperlink["https://learn.adafruit.com/introducing-trinket"]{Adafruit’s Trinket}}: The mini microcontroller that drives the hardware. Make sure to buy the 5V, not the 3V or the project will not work. It is available for sale directly from the manufaturer @hyperlink["https://www.adafruit.com/products/1501"]{Adafruit}, but I bought it on @hyperlink["http://www.ebay.com/itm/181250024010"]{eBay} because the shipping was cheaper.}
 @item{
  @margin-note{
   @bold{SPST}: Single pole, single throw. Only two terminals.

   @bold{Normally open}: The circuit is open when when the button is unpressed and closed (current goes through) when the button is pressed.

   @bold{Momentary}: The circuit stays closed only while the button is pressed—think of a regular key on a computer keyboard, as opposed to a latching switch which works like Caps Lock.
  }

  @bold{@hyperlink["http://www.ebay.com/itm/301599246336"]{Footswitches}}: SPST, normally open, momentary footwitches. I installed two and the microcontroller can handle one more. The other two GPIO (#3 and #4) are shared with the USB interface, which is used to the connect to the computer, so they are not available.}
 @item{@bold{Enclosure}: An Altoids tin.}
 @item{@bold{Micro-B USB cable}.}]

@section[#:tag "setup"]{Setup}

The wiring is the same as in @hyperlink["https://learn.adafruit.com/trinket-usb-keyboard/wiring"]{this project}. One connector of each of the buttons goes to ground (GND) and the other connectors go to #0 and #2. Power comes from the computer via the USB cable, no extra source is necessary.

Drill holes in the Altoids tin for the buttons and the USB port using a Dremel and a screwdriver. Solder the circuit and glue the microcontroller next to the side.

@hyperlink["https://learn.adafruit.com/trinket-usb-keyboard/code"]{Install the library} @tt{TrinketKeyboard} to the Arduino IDE.

Upload @hyperlink["https://git.leafac.com/programmable-foot-keyboard"]{the code} to the microcontroller using the Arduino IDE following @hyperlink["https://learn.adafruit.com/introducing-trinket/setting-up-with-arduino-ide"]{these instructions}.

@section[#:tag "usage"]{Usage}

Each of the buttons acts as a key on the computer keyboard. Pressing both buttons together changes to a different @emph{bank} and the buttons act as different keys on the computer keyboard. Pressing both buttons and holding for a few seconds resets to the initial bank.

@tabular[#:style 'boxed
         #:sep @hspace[1]
         #:row-properties '(bottom-border)
         `((, @bold{Bank} , @bold{Left button} , @bold{Right button})
           ("Scroll" "↑" "↓")
           ("Record" "" "R")
           ("Switch tabs" "⇧ ^ ⇥" "^ ⇥")
           ("Switch windows" "⇧ ⌘ ⇥" "⌘ ⇥"))]

@section[#:tag "configuration"]{Configuration}

Configure by changing the source code and uploading it again.

@section[#:tag "references"]{References}

@itemlist[
 @item{@hyperlink["https://learn.adafruit.com/trinket-usb-keyboard"]{https://learn.adafruit.com/trinket-usb-keyboard}}
 @item{@hyperlink["https://learn.adafruit.com/trinket-usb-keyboard/code"]{https://learn.adafruit.com/trinket-usb-keyboard/code}}
 @item{@hyperlink["https://learn.adafruit.com/trinket-usb-keyboard/prank-example"]{https://learn.adafruit.com/trinket-usb-keyboard/prank-example}}
 @item{@hyperlink["https://github.com/adafruit/Adafruit-Trinket-USB/"]{https://github.com/adafruit/Adafruit-Trinket-USB/}}
 @item{@hyperlink["https://github.com/adafruit/Adafruit-Trinket-USB/blob/51f208bc569dd79d7357f16d548ed0c43f4927e8/TrinketKeyboard/TrinketKeyboard.h"]{https://github.com/adafruit/Adafruit-Trinket-USB/blob/51f208bc569dd79d7357f16d548ed0c43f4927e8/TrinketKeyboard/TrinketKeyboard.h}}
]