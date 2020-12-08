# BostonHacks
# Water Consumption Log

"""when compiling use water(Log())"""
import math
class Log: 
  def __init__(self):
    #initializes the days of the week as variables

    self.dailyTotal = 0.0
    self.dailyAverage = 0.0
    self.weeklyTotal = 0.0
    self.weeklyAverage = 0.0
    self.monthlyTotalEstimate = 0.0
    self.yearlyTotalEstimate = 0.0

  def log_consumption(self):
    self.dailyTotal = int(input('Enter the number of baths you take in one day: ')) * 36.0
    self.dailyTotal += int(input('Enter the number of times you flush the toilet in one day: ')) * 3.0
    showerMinutes = int(input('Enter the number of minutes you spent in the shower: '))
    showerNumber = int(input('Enter the number of showers you took today: '))
    self.dailyTotal += (showerMinutes * showerNumber) * 2.0
    self.dailyTotal += int(input('Enter the number times you ran the washing machine today: ')) * 15.0
    self.dailyTotal += int(input('Enter the number times you ran the dishwasher today: ')) * 6.0
    handwashMin = int(input('Enter the number of minutes you spend hand washing dishes today: '))
    handwashTimes = int(input('Enter the number of times you hand wash dishes today: '))
    self.dailyTotal += handwashMin * handwashTimes #it is one gallon per minute spend handwashing dishes
    drinkWaterTime = int(input('Enter the number of times you drank water today: '))
    drinkWaterOunce = int(input('Enter the number of ounces of water you drank each time: '))
    self.dailyTotal += drinkWaterTime * drinkWaterOunce * 0.0078125 
  def reset_day(self):
    self.dailyTotal = 0.0
  def calculate_averages(self):
    """ calculates the daily/weekly/monthly/yearly averages
    """
    self.monthlyTotalEstimate = self.weeklyTotal * 4
    self.weeklyAverage = self.monthlyTotalEstimate / 7
    self.yearlyTotalEstimate = self.monthlyTotalEstimate * 12

  
