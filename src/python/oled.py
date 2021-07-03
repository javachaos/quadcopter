#!/usr/bin/python
import Adafruit_SSD1306
import Image
import ImageDraw
import ImageFont


class OLED:
    __disp = None
    __font = None
    __padding = 0
    __top     = 0
    __bottom  = 0
    __image = None
    __fill = 0
    __line = 0
    
    def __init__(self,RST="P9_12"):
      # RST is Beaglebone Black pin configuration:
      # 128x32 display with hardware I2C:
      self.__disp = Adafruit_SSD1306.SSD1306_128_32(rst=RST)
      #self.__disp = Adafruit_SSD1306.SSD1306_128_32(rst=RST, i2c_bus=1)
      # Initialize library.
      self.__disp.begin()
      # Clear display.
      self.__disp.clear()
      self.__disp.display()
      # Load default font.
      self.__font = ImageFont.load_default()
      # Text alignment
      self.__padding = 2
      self.__top = self.__padding
      self.__bottom = self.__disp.height - self.__padding
      self.__cursor = self.__padding
      self.__line = self.__padding
      self.__fill = 255

    ''' Clear and write a string to the display. 
        Starting at x and y pixels from top left. 
    '''
    def write_str(self,str,x=0,y=0):
      if str is not None and len(str) > 0 :
        self.__disp.clear()
        self.__line = 0  
        self.__image = Image.new('1', (self.__disp.width, self.__disp.height))
        draw = ImageDraw.Draw(self.__image)
        
        # Get the size of the text horizontally
        size = draw.textsize(str,  font=self.__font)
        if size[0] > self.__disp.width:
          for chunk in self.chunks(str,self.__disp.width / draw.textsize(" ", font=self.__font)[0]):
            draw.text((self.__padding+x, self.__top+self.__line+y), chunk,  font=self.__font, fill=self.__fill)
            self.__line += size[1]
        else:
          # Write two lines of text.
          draw.text((self.__padding+x, self.__top+y), str,  font=self.__font, fill=self.__fill)
          self.__line+=1
        # Display image.
        self.__disp.image(self.__image)
        self.__disp.display()

    ''' Scroll the text str about the verticle axis 
        with a default stepping of 1px per iteration.
    '''
    def scroll_text(self, str,stepping=1):
      text_height = 0
      self.__image = Image.new('1', (self.__disp.width, self.__disp.height))
      draw = ImageDraw.Draw(self.__image)
      for chunk in self.chunks(str,self.__disp.width / draw.textsize(" ", font=self.__font)[0]):
        text_height+=1
      size = draw.textsize(str,  font=self.__font)
      for y in range(-(text_height+self.__disp.height),size[1] * text_height + self.__padding, stepping):
        self.write_str(str,0,-y - stepping / 2)
    
    def chunks(self,str, chunk_size):
      '''Produce `chunk_size`-character chunks from `str`.'''
      strings = str.split(" ") 
      chunks = ""
      for s in strings:
        if len(s) + len(chunks) >= chunk_size:
          yield chunks
          chunks = ""
        chunks += s + " "
      yield chunks


if __name__ == "__main__":
    oled = OLED()
    oled.write_str("Quadcopter v0.1");
