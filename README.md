# ParkinsonWatch
A clone of [EmmaWatch](http://mashable.com/2017/05/10/microsoft-emma-watch-helps-woman-with-parkinsons-write-again/#duz6bHiLZOqT) to help reduce the shakes from Parkinsons 

This Arduino sketch works with a armband with 4 pager motors embedded into a elastic strap. Each motor is connected to a separate digital input. There are two patterns programmed into the armband. The settings for each pattern can be changed via serial commands to fine tune the settings for the particular person.  

Serial messages must end with "#" and contain 1 pattern and 2-3 parameters. 

**Patterns:**
- Sequential (1) - Each loop the next motor in the sequence will be turned on. 
   - Parameter 1 - Length of the motor on. Units in miliseconds 
   - Parameter 2 - Length of the motor off. Units in miliseconds 
- Random (2) - Motors are randomly turned on and off. 
   - Parameter 1 - Length of the motor on. Units in miliseconds 
   - Parameter 2 - Length of the motor off. Units in miliseconds 
   - Parameter 3 - The amount of motors that are randomly turned on each loop. 

**Example:**

2, 100, 500, 1#

In this example the armband will be switched to the random pattern (2) 0.1 second motor run time with a pause of 0.5 seconds and one motor active at a time.


<blockquote class="instagram-media" data-instgrm-captioned data-instgrm-version="7" style=" background:#FFF; border:0; border-radius:3px; box-shadow:0 0 1px 0 rgba(0,0,0,0.5),0 1px 10px 0 rgba(0,0,0,0.15); margin: 1px; max-width:658px; padding:0; width:99.375%; width:-webkit-calc(100% - 2px); width:calc(100% - 2px);"><div style="padding:8px;"> <div style=" background:#F8F8F8; line-height:0; margin-top:40px; padding:50.0% 0; text-align:center; width:100%;"> <div style=" background:url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACwAAAAsCAMAAAApWqozAAAABGdBTUEAALGPC/xhBQAAAAFzUkdCAK7OHOkAAAAMUExURczMzPf399fX1+bm5mzY9AMAAADiSURBVDjLvZXbEsMgCES5/P8/t9FuRVCRmU73JWlzosgSIIZURCjo/ad+EQJJB4Hv8BFt+IDpQoCx1wjOSBFhh2XssxEIYn3ulI/6MNReE07UIWJEv8UEOWDS88LY97kqyTliJKKtuYBbruAyVh5wOHiXmpi5we58Ek028czwyuQdLKPG1Bkb4NnM+VeAnfHqn1k4+GPT6uGQcvu2h2OVuIf/gWUFyy8OWEpdyZSa3aVCqpVoVvzZZ2VTnn2wU8qzVjDDetO90GSy9mVLqtgYSy231MxrY6I2gGqjrTY0L8fxCxfCBbhWrsYYAAAAAElFTkSuQmCC); display:block; height:44px; margin:0 auto -44px; position:relative; top:-22px; width:44px;"></div></div> <p style=" margin:8px 0 0 0; padding:0 4px;"> <a href="https://www.instagram.com/p/BaLapWXhdjF/" style=" color:#000; font-family:Arial,sans-serif; font-size:14px; font-style:normal; font-weight:normal; line-height:17px; text-decoration:none; word-wrap:break-word;" target="_blank">Helped a friend make a clone of the EmmaWatch. It should help people with Parkinson&#39;s tremors. Source code and instructions below. #arduino #disability #tremors #makers #makersgonnamake</a></p> <p style=" color:#c9c8cd; font-family:Arial,sans-serif; font-size:14px; line-height:17px; margin-bottom:0; margin-top:8px; overflow:hidden; padding:8px 0 7px; text-align:center; text-overflow:ellipsis; white-space:nowrap;">A post shared by Steven Smethurst (@funvill) on <time style=" font-family:Arial,sans-serif; font-size:14px; line-height:17px;" datetime="2017-10-13T06:36:59+00:00">Oct 12, 2017 at 11:36pm PDT</time></p></div></blockquote> <script async defer src="//platform.instagram.com/en_US/embeds.js"></script>