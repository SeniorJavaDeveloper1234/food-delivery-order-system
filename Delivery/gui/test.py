import delivery

print("\n=== Delivery System PYD Test (Both createOrder methods) ===\n")

ds = delivery.DeliverySystem()

clients = ds.clients()
couriers = ds.couriers()
menu = ds.menu()
orders = ds.orders()


client = delivery.Client(10, "John", "Doe", "111-222", "Kyiv")
clients.add(client)


courier1 = delivery.Courier(20, "Alex", "Smith", "333-444", True)
courier2 = delivery.Courier(21, "Bob", "Lee", "555-777", True)
couriers.add(courier1)
couriers.add(courier2)

item1 = delivery.MenuItem(1, "Pizza", "Cheese pizza", 199.0)
item2 = delivery.MenuItem(2, "Cola",  "0.5L bottle", 39.0)
menu.add(item1)
menu.add(item2)

print("Test data added OK\n")



print("--- TEST 1: createOrder(clientId, [item_ids]) ---")

order1 = ds.createOrder(10, [1, 2])

assert order1 is not None, "order1 returned None!"

print("Order1 created with ID:", order1.getId())
print("Order1 total:", order1.getTotalPrice())
print("Order1 items count:", len(order1.getItems()))

expected1 = item1.getPrice() + item2.getPrice()
assert abs(order1.getTotalPrice() - expected1) < 0.0001

print("Old createOrder() test passed!\n")



print("--- TEST 2: createOrder(clientId, [OrderItem]) ---")

order_item1 = delivery.OrderItem(1, "Pizza", 199.0, 2)  
order_item2 = delivery.OrderItem(2, "Cola",   39.0, 3) 

order2 = ds.createOrder(10, [order_item1, order_item2])

assert order2 is not None, "order2 returned None!"

print("Order2 created with ID:", order2.getId())
print("Order2 total:", order2.getTotalPrice())
print("Order2 items count:", len(order2.getItems()))

expected2 = 2 * 199.0 + 3 * 39.0
print("Expected total:", expected2)

assert abs(order2.getTotalPrice() - expected2) < 0.0001

print("New createOrder() test passed!\n")



print("--- Repository checks ---")

all_orders = orders.getAll()
print("Total orders in repository:", len(all_orders))
assert len(all_orders) >= 2

client_orders = ds.getClientOrders(10)
print("Orders for client 10:", len(client_orders))
assert len(client_orders) >= 2

print("\n=== ALL TESTS PASSED SUCCESSFULLY ===\n")
