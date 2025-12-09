from PyQt5.QtWidgets import QWidget, QVBoxLayout, QPushButton, QHBoxLayout
from widgets.ClientTable import ClientTable
from windows.AddClientWindow import AddClientWindow
from windows.EditClientWindow import EditClientWindow

class ClientsPage(QWidget):
    def __init__(self, adapter):
        super().__init__()
        self.adapter = adapter

        self.table = ClientTable()
        self.refresh_btn = QPushButton("Refresh List")
        self.add_btn = QPushButton("Add Client")
        self.edit_btn = QPushButton("Edit Client")

        top = QHBoxLayout()
        top.addWidget(self.refresh_btn)
        top.addWidget(self.add_btn)
        top.addWidget(self.edit_btn)

        layout = QVBoxLayout()
        layout.addLayout(top)
        layout.addWidget(self.table)
        self.setLayout(layout)

        self.refresh_btn.clicked.connect(self.load_clients)
        self.add_btn.clicked.connect(self.add_client)
        self.edit_btn.clicked.connect(self.edit_client)

        self.load_clients()

    def load_clients(self):
        data = self.adapter.get_clients()
        self.table.update_data(data)

    def add_client(self):
        win = AddClientWindow(self.adapter, self)
        if win.exec_():
            self.load_clients()

    def edit_client(self):
        row = self.table.currentRow()
        if row < 0:
            return

        client_id = int(self.table.item(row, 0).text())
        client = self.adapter.find_client(client_id)

        win = EditClientWindow(self.adapter, client, self)
        if win.exec_():
            self.load_clients()
