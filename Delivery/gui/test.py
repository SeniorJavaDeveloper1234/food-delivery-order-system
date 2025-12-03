import delivery

print("\n=== Delivery System PYD Test ===\n")

ds = delivery.DeliverySystem()

clients = ds.clients()
couriers = ds.couriers()
menu = ds.menu()
orders = ds.orders()

print("Repositories loaded OK")

client = delivery.Client(1, "John", "Doe", "111-222", "Kyiv")
clients.add(client)
print("Client added:", client.getFirstName(), client.getLastName())

courier = delivery.Courier(1, "Alex", "Smith", "333-444", True)
couriers.add(courier)
print("Courier added:", courier.getFirstName(), courier.getLastName())

item = delivery.MenuItem(1, "Pizza", "Cheese pizza", 199.0)
menu.add(item)
print("Menu item added:", item.getName(), item.getPrice())

order_item = delivery.OrderItem(1, "Pizza", 199.0, 2)
print("OrderItem test:", order_item.getName(), "x", order_item.getQuantity())

item_ids = [item.getId()]    

order = ds.createOrder(1, item_ids)

print("\nOrder created with ID:", order.getId())
print("Client ID:", order.getClientId())
print("Total price:", order.getTotalPrice())
print("Initial status:", order.getStatusString())


order.setStatus(delivery.OrderStatus.Preparing)
print("Updated status:", order.getStatusString())

order_item.setQuantity(3)
order.calculateTotalPrice()
print("Updated total after quantity change:", order.getTotalPrice())


found = orders.findById(order.getId())
print("\nFind by ID:", "OK" if found else "NOT FOUND")

client_orders = ds.getClientOrders(1)
print("Client orders:", len(client_orders))

print("\n=== TEST FINISHED SUCCESSFULLY ===\n")
