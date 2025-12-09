import delivery

class DeliveryAdapter:

    def __init__(self):
        self.ds = delivery.DeliverySystem()

    def get_clients(self):
        return self.ds.clients().getAll()

    def add_client(self, client_id, first, last, phone, address):
        client = delivery.Client(client_id, first, last, phone, address)
        self.ds.clients().add(client)

    def update_client(self, client_id, first, last, phone, address):
        c = self.ds.clients().findById(client_id)
        if c:
            c.setFirstName(first)
            c.setLastName(last)
            c.setPhone(phone)
            c.setAddress(address)
            return True
        return False

    def delete_client(self, client_id):
        return self.ds.clients().remove(client_id)

    def find_client(self, client_id):
        return self.ds.clients().findById(client_id)

    def get_couriers(self):
        return self.ds.couriers().getAll()

    def add_courier(self, cid, first, last, phone, available=True):
        courier = delivery.Courier(cid, first, last, phone, available)
        self.ds.couriers().add(courier)

    def update_courier(self, courier_id, first, last, phone, available):
        c = self.ds.couriers().findById(courier_id)
        if c:
            c.setFirstName(first)
            c.setLastName(last)
            c.setPhone(phone)
            c.setAvailable(available)
            return True
        return False

    def delete_courier(self, courier_id):
        return self.ds.couriers().remove(courier_id)

    def set_courier_available(self, courier_id, is_available):
        self.ds.couriers().setCourierAvailability(courier_id, is_available)

    def get_menu(self):
        return self.ds.menu().getAll()

    def add_menu_item(self, mid, name, desc, price):
        item = delivery.MenuItem(mid, name, desc, price)
        self.ds.menu().add(item)

    def update_menu_item(self, item_id, name, desc, price):
        item = self.ds.menu().findById(item_id)
        if item:
            item.setName(name)
            item.setDescription(desc)
            item.setPrice(price)
            return True
        return False

    def delete_menu_item(self, item_id):
        return self.ds.menu().remove(item_id)

    def get_orders(self):
        return self.ds.orders().getAll()

    def get_orders_by_client(self, client_id):
        return self.ds.getClientOrders(client_id)

    def get_orders_by_courier(self, courier_id):
        return self.ds.getCourierOrders(courier_id)

    def create_order_by_ids(self, client_id, item_ids):
        return self.ds.createOrder(client_id, item_ids)

    def create_order_by_items(self, client_id, py_items):
        items = []
        for x in py_items:
            oi = delivery.OrderItem(x["id"], x["name"], x["price"], x["qty"])
            items.append(oi)
        return self.ds.createOrder(client_id, items)

    def create_order_item(self, menu_id, name, price, qty):
        return delivery.OrderItem(menu_id, name, price, qty)

    def create_order_with_items(self, client_id, items):
        return self.ds.createOrder(client_id, items)

    def update_order_status(self, order_id, status):
        return self.ds.orders().updateStatus(order_id, status)


    def complete_order(self, order_id):
        return self.ds.completeOrder(order_id)

    def cancel_order(self, order_id):
        return self.ds.cancelOrder(order_id)

    def calc_total(self, py_items):
        total = 0.0
        for item in py_items:
            total += item["price"] * item["qty"]
        return total
