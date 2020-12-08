# BostonHacks2020
# Water Consumption
# DripBit
# Mikayla Steinberg, Magda Ellis, Zachary Fishman, Tony Yang

"""when compiling use water(Log())""" 

from weeklog import Log
import math

def view_consumption(user):
  """ Allows user to view their water consumption
  """
  print('Your water consumption today:', user.dailyTotal,'gallons')
  print('Your water consumption this week:', user.weeklyTotal,'gallons')
  print('Your water consumption this month:', user.monthlyTotalEstimate,'gallons')
  print('Your water consumption this year:', user.yearlyTotalEstimate,'gallons')
  print('Your average daily water consumption:', user.dailyAverage,'gallons')
  print('Your average weekly water consumption:', user.weeklyAverage, 'gallons')

def display_menu():
    """ prints a menu of options
    """  
    print()
    print('(1) Log in todays water consumption')
    print('(2) Log in your weekly water consumption')
    print('(3) View your water consumption')
    print('(4) Your consumption vs. the World')
    print('(5) Learn about our mission')
    print('(6) Learn about water consumption')
    print('(7) Our sources')
    print('(8) Quit')

def water(user):
    """ the main user-interaction loop
    """
    print()
    print('Welcome to DripBit! What would you like to do?')
    while True:
        display_menu()
        choice = int(input('Enter your choice: '))
        print()

        if choice == 1:
          #call a separate function here with user input
          #go to log class and ask for day and if it is a new week
          user.log_consumption()
        elif choice == 2:
          #do a while loop that logs in the information 7 times
          times = 1 
          while times < 8:
            print('Day', times)
            user.log_consumption()
            user.weeklyTotal += user.dailyTotal
            user.reset_day()
            times += 1
          user.dailyAverage = user.weeklyTotal / 7
        elif choice == 3:
          #view water consumption averages
          user.calculate_averages()
          view_consumption(user)
        elif choice == 4:
          #comparison of user's water consumption to the world
          world = 10002.40627
          india = 446.186597
          usa = 1002.26876
          germany = 225.867105
          worldDiff = user.dailyAverage - world
          indiaDiff = user.dailyAverage - india
          usaDiff = user.dailyAverage - usa
          germanyDiff = user.dailyAverage - germany
          print('Your daily water consumption is ', user.dailyAverage, ' gallons of water per day.')
          print('The daily water consumption in the United States is ', usa, ' gallons of water per day.')
          if (usaDiff > 0):
            print('You use more water than the average person in the United States per day. You used ', usaDiff, 'more gallons of water than the average person in the United States.')
          elif (usaDiff == 0):
            print('You use the same amount of water per day as the average person in the United States.')
          elif (usaDiff < 0):
            print('Congratulations! You use less water than the average person in the United States! The average person in the United States uses ', usaDiff * (-1), ' more gallons than you do per day.')
          print('The annual water consumption in India is ', india, ' gallons of water per day.')
          if (indiaDiff > 0):
            print('You use more water than the average person in India per day. You used ', indiaDiff, 'more gallons of water than the average person in India.')
          elif (indiaDiff == 0):
            print('You use the same amount of water per day as the average person in India.')
          elif (indiaDiff < 0):
            print('Congratulations! You use less water than the average person in India! The average person in India uses ', indiaDiff * (-1), ' more gallons than you do per day.')
          print('The annual water consumption in Germany is ', germany, ' gallons of water per day.')
          if (germanyDiff > 0):
            print('You use more water than the average person in Germany per day. You used ', germanyDiff, 'more gallons of water than the average person in Germany.')
          elif (germanyDiff == 0):
            print('You use the same amount of water per day as the average person in Germany.')
          elif (germanyDiff < 0):
            print('Congratulations! You use less water than the average person in Germany! The average person in Germany uses ', germanyDiff * (-1), ' more gallons than you do per day.')
          print('The annual water consumption in the world is ', world, ' gallons of water per day.')
          if (worldDiff > 0):
            print('You use more water than the average person in the world per day. You used ', worldDiff, 'more gallons of water than the average person in the world.')
          elif (worldDiff == 0):
            print('You use the same amount of water per day as the average person in the world.')
          elif (worldDiff < 0):
            print('Congratulations! You use less water than the average person in the world! The average person in the world uses ', worldDiff * (-1), ' more gallons than you do per day.')
          print()
          print('If you would like to find ways to decrease your water consumption, go to our water consumption basics.')

        elif choice == 5:
          #mission statement
          print('Our mission at DripBit is to help you limit your water consumption everyday. We want to make it as easy as possible for you to log how much water you use each day. With this, you can easily see how much water you are using in a day. We ultimately hope to lower the global water consumption considerably and help our planet.')
        elif choice == 6: 
          # water consumption basics 
          print('The average person uses 101.5 gallons of water per day. The world uses 9,087 billion cubic meters of water per year. Thats a lot of water! And only about 2.5% of water on Earth is fresh water and with the effects of climate change our sources are dwindling! Its very important that we save water so that there is enough fresh water for everyone on Earth. Some ways one can reduce their water usage is as follows:')
          print('')
          print('1. Take showers instead of baths.')
          print('2. When rinsing vegetables or fruits use a bowl instead of running water.')
          print('3. Fully load the dishwasher or washing machine and run the eco-washing cycle.')
          print('4. When washing manually, wash in a full sink rather than running water.')
          print('5. Make sure to fully shut off faucets after using them.')
          print('In conclusion, its important for all of us to be concious of our water consumption and to take into account everytime we turn on a sink, flush a toilet, or run a dishwasher. The water really adds up!')
        elif choice == 7: 
          #print sources
          print('1) https://www.epa.gov/watersense/statistics-and-facts')
          print('2)https://judo.eu/en/the-world-water-day-2019/')
          print('3) https://www.phila.gov/water/educationoutreach/Documents/Homewateruse_IG5.pdf')
          print('4) https://www.scientificamerican.com/article/graphic-science-how-much-water-nations-consume/')
          print('5) https://www.usgs.gov/special-topic/water-science-school/science/water-qa-how-much-water-do-i-use-home-each-day?qt-science_center_objects=0#qt-science_center_objects')
          print('6) https://www.worldometers.info/water/')
        elif choice == 8:
          #quit
          print('Have a nice day!')
          break
        else: 
          print('Invalid Choice, please try again') 
    print()
    print('Thank you for your efforts in lowering your water consumption!')
