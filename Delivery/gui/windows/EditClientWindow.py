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
        self.adapter.update_client(
            self.client.getId(),
            self.first_field.text(),
            self.last_field.text(),
            self.phone_field.text(),
            self.address_field.text()
        )
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
