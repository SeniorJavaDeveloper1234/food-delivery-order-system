

from PyQt5.QtWidgets import QTableWidget, QTableWidgetItem, QHeaderView

class OrderTable(QTableWidget):
    def __init__(self):
        super().__init__()
        self.setColumnCount(7)
        self.setHorizontalHeaderLabels([
            "ID", "Client", "Courier", "Items", "Status", "Total Price(UAH)", "Created At"
        ])

        self.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.setSelectionBehavior(self.SelectRows)
        self.setSelectionMode(self.SingleSelection)
        self.setEditTriggers(self.NoEditTriggers)

    def update_data(self, orders):
        self.setRowCount(len(orders))
        for row, o in enumerate(orders):

            
            items = o.getItems()  
            items_str = ", ".join([
                f"{item.getName()} x{item.getQuantity()}"
                for item in items
            ])

            self.setItem(row, 0, QTableWidgetItem(str(o.getId())))
            self.setItem(row, 1, QTableWidgetItem(str(o.getClientId())))
            self.setItem(row, 2, QTableWidgetItem(str(o.getCourierId())))
            self.setItem(row, 3, QTableWidgetItem(items_str)) 
            self.setItem(row, 4, QTableWidgetItem(o.getStatusString()))
            self.setItem(row, 5, QTableWidgetItem(str(o.getTotalPrice())))
            self.setItem(row, 6, QTableWidgetItem(o.getCreatedAt()))
