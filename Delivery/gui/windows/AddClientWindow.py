from PyQt5.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel,
    QLineEdit, QPushButton, QMessageBox
)

class AddClientWindow(QDialog):
    def __init__(self, adapter, parent=None):
        super().__init__(parent)
        self.adapter = adapter

        self.setWindowTitle("Add Client")
        self.setMinimumWidth(350)

        self.first_field = QLineEdit()
        self.last_field = QLineEdit()
        self.phone_field = QLineEdit()
        self.address_field = QLineEdit()

        save_btn = QPushButton("Save")
        cancel_btn = QPushButton("Cancel")

        layout = QVBoxLayout()

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

    def show_error(self, text):
        QMessageBox.critical(self, "Error", text)

    def save(self):
        first = self.first_field.text().strip()
        last = self.last_field.text().strip()
        phone = self.phone_field.text().strip()
        address = self.address_field.text().strip()

        if not first or not last or not phone or not address:
            self.show_error("All fields must be filled.")
            return

        self.adapter.add_client(first, last, phone, address)

        QMessageBox.information(self, "Success", "Client added successfully!")
        self.accept()
