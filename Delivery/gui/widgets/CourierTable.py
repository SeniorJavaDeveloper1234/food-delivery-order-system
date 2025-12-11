

from PyQt5.QtWidgets import QTableWidgetItem, QHeaderView, QTableWidget

class CourierTable(QTableWidget):
    def __init__(self):
        super().__init__()
        self.setColumnCount(5)
        self.setHorizontalHeaderLabels(["ID", "First Name", "Last Name", "Phone", "Available"])

        self.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.setSelectionBehavior(self.SelectRows)
        self.setSelectionMode(self.SingleSelection)
        self.setEditTriggers(self.NoEditTriggers)

    def update_data(self, couriers):
        self.setRowCount(len(couriers))
        for row, c in enumerate(couriers):
            self.setItem(row, 0, QTableWidgetItem(str(c.getId())))
            self.setItem(row, 1, QTableWidgetItem(c.getFirstName()))
            self.setItem(row, 2, QTableWidgetItem(c.getLastName()))
            self.setItem(row, 3, QTableWidgetItem(c.getPhone()))
            self.setItem(row, 4, QTableWidgetItem("Yes" if c.isAvailable() else "No"))
