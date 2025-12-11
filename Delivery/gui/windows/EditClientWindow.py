

from PyQt5.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel,
    QLineEdit, QPushButton, QMessageBox
)

class EditClientWindow(QDialog):
    def __init__(self, adapter, client, parent=None):
        super().__init__(parent)
        self.adapter = adapter
        self.client = client

        self.setWindowTitle("Edit Client")
        self.setMinimumWidth(350)

        self.id_field = QLineEdit(str(client.getId()))
        self.id_field.setReadOnly(True)

        self.first_field = QLineEdit(client.getFirstName())
        self.last_field = QLineEdit(client.getLastName())
        self.phone_field = QLineEdit(client.getPhone())
        self.address_field = QLineEdit(client.getAddress())

        save_btn = QPushButton("Save")
        delete_btn = QPushButton("Delete")
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

        btns = QHBoxLayout()
        btns.addWidget(save_btn)
        btns.addWidget(delete_btn)
        btns.addWidget(cancel_btn)

        layout.addLayout(btns)
        self.setLayout(layout)

        save_btn.clicked.connect(self.save)
        delete_btn.clicked.connect(self.delete)
        cancel_btn.clicked.connect(self.reject)

    def save(self):
        first = self.first_field.text().strip()
        last = self.last_field.text().strip()
        phone = self.phone_field.text().strip()
        address = self.address_field.text().strip()

        if first == "" or last == "" or phone == "" or address == "":
            QMessageBox.warning(self, "Error", "All fields must be filled!")
            return

        ok = self.adapter.update_client(
            self.client.getId(),
            first,
            last,
            phone,
            address
        )

        if not ok:
            QMessageBox.critical(self, "Error", "Failed to update client — not found.")
            return

        self.accept()

    def delete(self):
        confirm = QMessageBox.question(
            self,
            "Confirmation",
            f"Delete client #{self.client.getId()}?",
            QMessageBox.Yes | QMessageBox.No
        )

        if confirm == QMessageBox.Yes:
            self.adapter.delete_client(self.client.getId())
            self.accept()
