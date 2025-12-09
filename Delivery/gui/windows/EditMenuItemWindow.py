from PyQt5.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel,
    QLineEdit, QPushButton, QMessageBox
)

class EditMenuItemWindow(QDialog):
    def __init__(self, adapter, item, parent=None):
        super().__init__(parent)
        self.adapter = adapter
        self.item = item

        self.setWindowTitle("Edit Menu Item")
        self.setMinimumWidth(350)

        self.id_field = QLineEdit(str(item.getId()))
        self.id_field.setReadOnly(True)

        self.name_field = QLineEdit(item.getName())
        self.desc_field = QLineEdit(item.getDescription())
        self.price_field = QLineEdit(str(item.getPrice()))

        save_btn = QPushButton("Save")
        delete_btn = QPushButton("Delete")
        cancel_btn = QPushButton("Cancel")

        layout = QVBoxLayout()
        layout.addWidget(QLabel("ID"))
        layout.addWidget(self.id_field)
        layout.addWidget(QLabel("Name"))
        layout.addWidget(self.name_field)
        layout.addWidget(QLabel("Description"))
        layout.addWidget(self.desc_field)
        layout.addWidget(QLabel("Price"))
        layout.addWidget(self.price_field)

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
        name = self.name_field.text()
        desc = self.desc_field.text()
        price = float(self.price_field.text())

        self.item.setName(name)
        self.item.setDescription(desc)
        self.item.setPrice(price)

        self.accept()

    def delete(self):
        confirm = QMessageBox.question(
            self,
            "Confirmation",
            f"Delete: {self.item.getName()}?",
            QMessageBox.Yes | QMessageBox.No
        )

        if confirm == QMessageBox.Yes:
            self.adapter.delete_menu_item(self.item.getId())
            self.accept()
