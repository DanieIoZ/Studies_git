from rosemary import Item, update
 

#============== QUALITY ======================

# / default /
def test_default_item_qual_changing():
    item = Item('Bread', days_left=3, quality=5)
    # Call to the tested function
    update(item)
    # Check the specification
    return item.quality == 4

def test_default_item_qual_lower_bound():
    item = Item('Bread', days_left=5, quality=0)
    # Call to the tested function
    update(item)
    # Check the specification
    return item.quality == 0

# def test_default_item_qual_upper_bound():
#     item = Item('Bread', days_left=5, quality=100)
#     # Call to the tested function
#     update(item)
#     return item.quality == 49

def test_default_item_qual_after_days_left():
    item = Item('Bread', days_left=1, quality=10)
    # Call to the tested function
    update(item)
    update(item)
    return item.quality == 7

# / diamond /
def test_diamond_qual_unchanged():
    item = Item('Diamond', days_left=13, quality=100)
    # Call to the tested function
    update(item)
    return item.quality == 100

# def test_diamond_qual_default_value():
#     item = Item('Diamond', days_left=13, quality=10)
#     # Call to the tested function
#     update(item)
#     return item.quality == 100

# / cheese /
def test_cheese_qual_changing():
    item = Item('Aged Brie', days_left=13, quality=10)
    # Call to the tested function
    update(item)
    return item.quality == 11

def test_cheese_qual_upper_bound():
    item = Item('Aged Brie', days_left=13, quality=50)
    # Call to the tested function
    update(item)
    return item.quality == 50

# def test_cheese_qual_lower_bound():
#     item = Item('Aged Brie', days_left=13, quality=-4)
#     # Call to the tested function
#     update(item)
#     return item.quality == 1

# / tickets /
def test_tickets_qual_10_plus():
    item = Item('Tickets', days_left=15, quality=5)
    # Call to the tested function
    for i in range(5):
        update(item)
    return item.quality == 10

def test_tickets_qual_6_to_10():
    item = Item('Tickets', days_left=10, quality=5)
    # Call to the tested function
    for i in range(5):
        update(item)
    return item.quality == 15

def test_tickets_qual_1_to_5():
    item = Item('Tickets', days_left=5, quality=5)
    # Call to the tested function
    for i in range(5):
        update(item)
    return item.quality == 20

def test_tickets_qual_to_0():
    item = Item('Tickets', days_left=0, quality=5)
    # Call to the tested function
    update(item)
    return item.quality == 0

def test_tickets_qual_upper_bound():
    item = Item('Tickets', days_left=4, quality=50)
    # Call to the tested function
    update(item)
    return item.quality == 50

# def test_tickets_qual_lower_bound():
#     item = Item('Tickets', days_left=4, quality=-5)
#     # Call to the tested function
#     update(item)
#     return item.quality == 3

#================ DAYS LEFT =====================

# / default item /
def test_default_item_days_left_changing():
    # Prepare for the test
    item = Item('Bread', days_left=3, quality=5)
    # Call to the tested function
    update(item)
    # Check the specification
    return item.days_left == 2

# / diamond /

def test_diamond_days_left_changing():
    item = Item('Diamond', days_left=10, quality=100)
    # Call to the tested function
    update(item)
    return item.days_left == 10

# / cheese /
def test_cheese_days_left_changing():
    item = Item('Aged Brie', days_left=10, quality=100)
    # Call to the tested function
    update(item)
    return item.days_left == 9


#==================== NAME ======================

 
def test_default_item_name_unchanged():
    item = Item('Bread', days_left=3, quality=5)
    # Call to the tested function
    oldName = item.name
    update(item)
    # Check the specification
    return item.name == oldName

def test_diamond_name_unchanged():
    item = Item('Diamond', days_left=3, quality=5)
    # Call to the tested function
    oldName = item.name
    update(item)
    # Check the specification
    return item.name == oldName

def test_cheese_name_unchanged():
    item = Item('Aged Brie', days_left=3, quality=5)
    # Call to the tested function
    oldName = item.name
    update(item)
    # Check the specification
    return item.name == oldName

def test_tickets_name_unchanged():
    item = Item('Tickets', days_left=3, quality=5)
    # Call to the tested function
    oldName = item.name
    update(item)
    # Check the specification
    return item.name == oldName