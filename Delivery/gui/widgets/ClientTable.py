from PyQt5.QtWidgets import QTableWidget, QTableWidgetItem

class ClientTable(QTableWidget):
    def __init__(self):
        super().__init__()
        self.setColumnCount(5)
        self.setHorizontalHeaderLabels(["ID", "First Name", "Last Name", "Phone", "Address"])

    def update_data(self, clients):
        self.setRowCount(len(clients))
        for row, c in enumerate(clients):
            self.setItem(row, 0, QTableWidgetItem(str(c.getId())))
            self.setItem(row, 1, QTableWidgetItem(c.getFirstName()))
            self.setItem(row, 2, QTableWidgetItem(c.getLastName()))
            self.setItem(row, 3, QTableWidgetItem(c.getPhone()))
            self.setItem(row, 4, QTableWidgetItem(c.getAddress()))
