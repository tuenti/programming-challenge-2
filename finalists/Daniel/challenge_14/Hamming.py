#!/bin/env /apps/tools/bin/python

# Copyright 2008 Altera Corporation.
# $Header: //depot/devenv/templates/python/basic_script_template.py#1 $

"""
http://users.cs.fiu.edu/~downeyt/cop3402/hamming.html
"""

# Altera specific conventions:
# - capitalize global, static constant variables
# - functions are lower_case_with_underscores_to_separate_words()
# - class names are CamelCaseToFollowPythonConventions


__author__ = "yltan"
__version__ = "1.1"
PROG = "Hamming"
__history__ = """
+-------------+----------+-----------+------------------------------------------------------------------------------
| Date        | Revision | Author    | Comment 
+-------------+----------+-----------+------------------------------------------------------------------------------
| 21 Jan 2011 | 1.1      | YLTan     | Completed FULL user/Developer manual.
|             |          |           | 2. Recreate new gui_output_file when load config.
+-------------+----------+-----------+------------------------------------------------------------------------------
"""


import optparse
import sys
import os
import re
import subprocess


class Hamming(object):
   """ Main Wrapper For GUI """
   def __init__(self):
      super(Hamming, self).__init__()

      
#---------------------------------------------
   def check(self):
      bitlength = len(self.code())
      parityLoc = 1
      errorBit = 0

      while bitlength > parityLoc:
         parity = self.getParityBit(parityLoc)
         if parity != 0:
            errorBit += parityLoc
         parityLoc *= 2
      
      return errorBit
      
#---------------------------------------------
   def genDataFromCode(self):
      parityLoc = 1
      self._data = []
      for (curLoc, bit) in enumerate(self.code()):
         if curLoc+1 == parityLoc:
            parityLoc *= 2
         else:
            self._data.append(bit)
#---------------------------------------------
   def genCodeFromData(self):
      self._code = []   # initialize
      self.genEmptyParityCodeFromData()
      
      for (curLoc,data) in enumerate(self._code):
         if data == '-':
            parity = self.getParityBit(curLoc+1)
            if self.isEven(parity):
               self._code[curLoc] = 0
            else:
               self._code[curLoc] = 1
#---------------------------------------------
   def getParityBit(self, loc):
      """ Find the parity bit for a given location.
      Eg 1:-
         loc = 2
         code = '011100101010'
         total = bit(1,2) + bit(5,6) + bit(9,10)
               = (1+1)    + (0+1)    + (0+1)
               = 4
         parity = 0

      Eg 2:-
         loc = 1
         code = '011100101000'
         total = bit(0,2,4,6,8,10)
               = 0+1+0+1+1+0
               = 3
         parity = 1

      """
      take = loc
      skip = loc
      total = 0
      for [x,bit] in enumerate(self._code[loc-1:]):
         if take == 0:
            if skip:
               skip -= 1
            if skip == 0:
               take = loc
               skip = loc
         elif bit == '-':
            take -= 1
         elif take:
            total += int(bit)
            take -= 1
      return 0 if self.isEven(total) else 1
#---------------------------------------------
   def genEmptyParityCodeFromData(self):
      """ self._data = [1,0,1,0,1,0,1,0]
      return [-,-,1,-,0,1,0,-,1,0,1,0]
      """
      parityLoc = 1  # Parity bit Location
      curLoc    = 1  # Current Location
      self._code = []
      for data in self._data:
         while curLoc == parityLoc:
            self._code.append('-')
            curLoc += 1
            parityLoc *= 2

         if curLoc != parityLoc:
            self._code.append(data)
            curLoc += 1
#---------------------------------------------
   def isEven(self, val):
      return False if val%2 else True
#---------------------------------------------
#---------------------------------------------
#---------------------------------------------
# --- Getter / Setter
#---------------------------------------------
   def data(self, val=None):
      """ Data (not including parity bits)
      Eg:-
         self.data('11010101010001') 
      """
      if val is None:
         return self._data
      else:
         self._data = [int(x) for x in str(val)]
         self.genCodeFromData()
#---------------------------------------------
   def code(self, val=None):
      """ Code (including parity bits)
      Eg:-
         self.code('11010101010001') 
      """
      if val is None:
         return self._code
      else:
         self._code = [int(x) for x in str(val)]
         self.genDataFromCode()
#---------------------------------------------

##############################################
##############################################
##############################################
### Main script
if __name__ == "__main__":
   a = Hamming()
   a.data('10011010')
   print "DATA:" + str(a.data())
   print "CODE:" + str(a.code())
   a.check()
   print "-------------------------------"
   b = Hamming()
   b.code("011100101011")
   print "DATA:" + str(b.data())
   print "CODE:" + str(b.code())
   b.check()
   print "-------------------------------"
