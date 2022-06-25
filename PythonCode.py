import re
import string
import collections


def AllItemCount():
    with open('GroceryList.txt') as GroceryList: # open input file and create a dictionary from the data
        itemCount = collections.Counter(line.strip() for line in GroceryList)

        for item in itemCount: # print each item and the times it occurs
            print('%s %d' %(item, itemCount[item]))

def UserItemCount(UserItem):
    UserItem = UserItem.capitalize() # so not case sensitive
    with open('GroceryList.txt') as GroceryList: # open input file
        ItemList = GroceryList.read()
        ItemCount = ItemList.count(UserItem) # count only user specified item
        return ItemCount # returns the amount of specified item occurence 

def ItemCounterHist():
    with open('frequency.dat', "w") as HistData: # open input file
        with open('GroceryList.txt') as GroceryList: # open output file
            ItemCounts = collections.Counter(line.strip() for line in GroceryList)

            for item in ItemCounts: # write items and their counts from input file to output file
                HistData.write('%s %d\n' %(item, ItemCounts[item]))

                if HistData.closed: # confirmation of successful file closure
                    print('File Closed')

        
    