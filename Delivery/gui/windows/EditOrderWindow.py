from PyQt5.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel,
    QLineEdit, QPushButton, QComboBox, QMessageBox
)
import delivery

class EditOrderWindow(QDialog):
    def __init__(self, adapter, order, parent=None):
        super().__init__(parent)
        self.adapter = adapter
        self.order = order

        self.setWindowTitle("Edit Order Status")
        self.setMinimumWidth(350)

        self.deleted = False   

        self.id_field = QLineEdit(str(order.getId()))
        self.id_field.setReadOnly(True)

        self.client_field = QLineEdit(str(order.getClientId()))
        self.client_field.setReadOnly(True)

        self.courier_field = QLineEdit(str(order.getCourierId()))
        self.courier_field.setReadOnly(True)

        self.status_box = QComboBox()
        self.status_box.addItems(["Pending", "Preparing", "Delivering", "Completed", "Cancelled"])
        self.status_box.setCurrentText(order.getStatusString())

        save_btn = QPushButton("Save")
        delete_btn = QPushButton("Delete Order")   
        cancel_btn = QPushButton("Cancel")

        layout = QVBoxLayout()
        layout.addWidget(QLabel("Order ID"))
        layout.addWidget(self.id_field)
        layout.addWidget(QLabel("Client ID"))
        layout.addWidget(self.client_field)
        layout.addWidget(QLabel("Courier ID"))
        layout.addWidget(self.courier_field)
        layout.addWidget(QLabel("Status"))
        layout.addWidget(self.status_box)

        row = QHBoxLayout()
        row.addWidget(save_btn)
        row.addWidget(delete_btn)
        row.addWidget(cancel_btn)

        layout.addLayout(row)
        self.setLayout(layout)

        save_btn.clicked.connect(self.save)
        delete_btn.clicked.connect(self.delete_order)   
        cancel_btn.clicked.connect(self.reject)

    def save(self):
        new_status = self.status_box.currentText()
        enum_value = getattr(delivery.OrderStatus, new_status)
        self.adapter.update_order_status(self.order.getId(), enum_value)
        self.accept()

    def delete_order(self):
        oid = self.order.getId()

        confirm = QMessageBox.question(
            self,
            "Delete Order",
            f"Are you sure you want to delete order #{oid}?",
            QMessageBox.Yes | QMessageBox.No
        )

        if confirm == QMessageBox.Yes:
            ok = self.adapter.delete_order(oid)

            if ok:
                self.deleted = True   
                QMessageBox.information(self, "Deleted", "Order deleted successfully.")
                self.accept()
            else:
                QMessageBox.warning(self, "Error", "Failed to delete order.")
