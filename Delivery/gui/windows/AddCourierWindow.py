

from PyQt5.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel,
    QLineEdit, QPushButton, QCheckBox, QMessageBox
)

class AddCourierWindow(QDialog):
    def __init__(self, adapter, parent=None):
        super().__init__(parent)
        self.adapter = adapter

        self.setWindowTitle("Add Courier")
        self.setMinimumWidth(350)

        self.first_field = QLineEdit()
        self.last_field = QLineEdit()
        self.phone_field = QLineEdit()
        self.available_box = QCheckBox("Available")
        self.available_box.setChecked(True)

        save_btn = QPushButton("Save")
        cancel_btn = QPushButton("Cancel")

        layout = QVBoxLayout()

        layout.addWidget(QLabel("First Name"))
        layout.addWidget(self.first_field)

        layout.addWidget(QLabel("Last Name"))
        layout.addWidget(self.last_field)

        layout.addWidget(QLabel("Phone"))
        layout.addWidget(self.phone_field)

        layout.addWidget(self.available_box)

        row = QHBoxLayout()
        row.addWidget(save_btn)
        row.addWidget(cancel_btn)

        layout.addLayout(row)
        self.setLayout(layout)

        save_btn.clicked.connect(self.save)
        cancel_btn.clicked.connect(self.reject)

    def show_error(self, text):
        QMessageBox.critical(self, "Error", text)

    def save(self):
        first = self.first_field.text().strip()
        last = self.last_field.text().strip()
        phone = self.phone_field.text().strip()
        available = self.available_box.isChecked()

        if not first or not last or not phone:
            self.show_error("All fields must be filled.")
            return

        self.adapter.add_courier(first, last, phone, available)

        QMessageBox.information(self, "Success", "Courier added successfully!")
        self.accept()
