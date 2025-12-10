import delivery

class DeliveryAdapter:

    def __init__(self):
        self.ds = delivery.DeliverySystem()

    def save(self):
        self.ds.saveAll()

    # -------- CLIENTS --------

    def get_clients(self):
        return self.ds.clients().getAll()

    def add_client(self, first, last, phone, address):
        client = delivery.Client(0, first, last, phone, address)
        self.ds.addClient(client)
        self.save()

    def update_client(self, client_id, first, last, phone, address):
        ok = self.ds.updateClient(client_id, first, last, phone, address)
        if ok:
            self.save()
        return ok

    def delete_client(self, client_id):
        ok = self.ds.removeClient(client_id)
        if ok:
            self.save()
        return ok

    def find_client(self, client_id):
        return self.ds.clients().findById(client_id)

    # -------- COURIERS --------

    def get_couriers(self):
        return self.ds.couriers().getAll()

    def add_courier(self, first, last, phone, available=True):
        courier = delivery.Courier(0, first, last, phone, available)
        self.ds.addCourier(courier)
        self.save()

    def update_courier(self, courier_id, first, last, phone, available):
        ok = self.ds.updateCourier(courier_id, first, last, phone, available)
        if ok:
            self.save()
        return ok

    def delete_courier(self, courier_id):
        ok = self.ds.removeCourier(courier_id)
        if ok:
            self.save()
        return ok

    # -------- MENU --------

    def get_menu(self):
        return self.ds.menu().getAll()

    def add_menu_item(self, name, desc, price):
        item = delivery.MenuItem(0, name, desc, price)
        self.ds.addMenuItem(item)
        self.save()

    def update_menu_item(self, item_id, name, desc, price):
        ok = self.ds.updateMenuItem(item_id, name, desc, price)
        if ok:
            self.save()
        return ok

    def delete_menu_item(self, item_id):
        ok = self.ds.removeMenuItem(item_id)
        if ok:
            self.save()
        return ok

    def search_menu(self, part):
        return self.ds.menu().searchByName(part)

    # -------- ORDERS --------

    def get_orders(self):
        return self.ds.orders().getAll()

    def get_orders_by_client(self, client_id):
        return self.ds.getClientOrders(client_id)

    def get_orders_by_courier(self, courier_id):
        return self.ds.getCourierOrders(courier_id)

    def create_order_by_ids(self, client_id, item_ids):
        order = self.ds.createOrder(client_id, item_ids)
        self.save()
        return order

    def create_order_by_items(self, client_id, py_items):
        items = [
            delivery.OrderItem(x["id"], x["name"], x["price"], x["qty"])
            for x in py_items
        ]
        order = self.ds.createOrder(client_id, items)
        self.save()
        return order

    def create_order_item(self, menu_id, name, price, qty):
        return delivery.OrderItem(menu_id, name, price, qty)

    def create_order_with_items(self, client_id, items):
        order = self.ds.createOrder(client_id, items)
        self.save()
        return order

    def update_order_status(self, order_id, status):
        ok = self.ds.orders().updateStatus(order_id, status)
        if ok:
            self.save()
        return ok

    def complete_order(self, order_id):
        ok = self.ds.completeOrder(order_id)
        if ok:
            self.save()
        return ok

    def cancel_order(self, order_id):
        ok = self.ds.cancelOrder(order_id)
        if ok:
            self.save()
        return ok

    def calc_total(self, py_items):
        return sum(item["price"] * item["qty"] for item in py_items)
