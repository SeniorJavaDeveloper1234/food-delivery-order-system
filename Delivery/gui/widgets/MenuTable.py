

from PyQt5.QtWidgets import QTableWidgetItem, QHeaderView, QTableWidget

class MenuTable(QTableWidget):
    def __init__(self):
        super().__init__()
        self.setColumnCount(4)
        self.setHorizontalHeaderLabels(["ID", "Name", "Description", "Price(UAH)"])

        self.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.setSelectionBehavior(self.SelectRows)
        self.setSelectionMode(self.SingleSelection)
        self.setEditTriggers(self.NoEditTriggers)

    def update_data(self, items):
        self.setRowCount(len(items))
        for row, m in enumerate(items):
            self.setItem(row, 0, QTableWidgetItem(str(m.getId())))
            self.setItem(row, 1, QTableWidgetItem(m.getName()))
            self.setItem(row, 2, QTableWidgetItem(m.getDescription()))
            self.setItem(row, 3, QTableWidgetItem(str(m.getPrice())))
