

from PyQt5.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel,
    QLineEdit, QPushButton, QCheckBox, QMessageBox
)

class EditCourierWindow(QDialog):
    def __init__(self, adapter, courier, parent=None):
        super().__init__(parent)
        self.adapter = adapter
        self.courier = courier

        self.setWindowTitle("Edit Courier")
        self.setMinimumWidth(350)

        self.id_field = QLineEdit(str(courier.getId()))
        self.id_field.setReadOnly(True)

        self.first_field = QLineEdit(courier.getFirstName())
        self.last_field = QLineEdit(courier.getLastName())
        self.phone_field = QLineEdit(courier.getPhone())
        self.available_box = QCheckBox("Available")
        self.available_box.setChecked(courier.isAvailable())

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
        layout.addWidget(self.available_box)

        row = QHBoxLayout()
        row.addWidget(save_btn)
        row.addWidget(delete_btn)
        row.addWidget(cancel_btn)

        layout.addLayout(row)
        self.setLayout(layout)

        save_btn.clicked.connect(self.save)
        delete_btn.clicked.connect(self.delete)
        cancel_btn.clicked.connect(self.reject)

    def save(self):
        ok = self.adapter.update_courier(
            self.courier.getId(),
            self.first_field.text(),
            self.last_field.text(),
            self.phone_field.text(),
            self.available_box.isChecked()
        )

        if ok:
            self.accept()
        else:
            QMessageBox.warning(self, "Error", "Courier was not updated.")

    def delete(self):
        confirm = QMessageBox.question(
            self,
            "Confirmation",
            f"Delete courier #{self.courier.getId()}?",
            QMessageBox.Yes | QMessageBox.No
        )

        if confirm == QMessageBox.Yes:
            self.adapter.delete_courier(self.courier.getId())
            self.accept()
