from PyQt5.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel,
    QLineEdit, QPushButton
)

class AddClientWindow(QDialog):
    def __init__(self, adapter, parent=None):
        super().__init__(parent)
        self.adapter = adapter

        self.setWindowTitle("Add Client")
        self.setMinimumWidth(350)

        self.id_field = QLineEdit()
        self.first_field = QLineEdit()
        self.last_field = QLineEdit()
        self.phone_field = QLineEdit()
        self.address_field = QLineEdit()

        save_btn = QPushButton("Save")
        cancel_btn = QPushButton("Cancel")

        layout = QVBoxLayout()
        layout.addWidget(QLabel("ID"))
        layout.addWidget(self.id_field)
        layout.addWidget(QLabel("First Name"))
        layout.addWidget(self.first_field)
        layout.addWidget(QLabel("Last Name"))
        layout.addWidget(self.last_field)
        layout.addWidget(QLabel("Phone"))
        layout.addWidget(self.phone_field)
        layout.addWidget(QLabel("Address"))
        layout.addWidget(self.address_field)

        buttons = QHBoxLayout()
        buttons.addWidget(save_btn)
        buttons.addWidget(cancel_btn)

        layout.addLayout(buttons)
        self.setLayout(layout)

        save_btn.clicked.connect(self.save)
        cancel_btn.clicked.connect(self.reject)

    def save(self):
        cid = int(self.id_field.text())
        first = self.first_field.text()
        last = self.last_field.text()
        phone = self.phone_field.text()
        address = self.address_field.text()

        self.adapter.add_client(cid, first, last, phone, address)
        self.accept()
