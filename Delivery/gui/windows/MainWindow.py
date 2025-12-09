from PyQt5.QtWidgets import (
    QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QPushButton, QStackedWidget
)

from services.DeliveryAdapter import DeliveryAdapter
from windows.ClientsPage import ClientsPage
from windows.CouriersPage import CouriersPage
from windows.MenuPage import MenuPage
from windows.OrdersPage import OrdersPage


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Food Delivery System")
        self.setGeometry(200, 150, 1100, 700)

        self.adapter = DeliveryAdapter()
        self.stack = QStackedWidget()

        self.pages = {
            "clients": ClientsPage(self.adapter),
            "couriers": CouriersPage(self.adapter),
            "menu": MenuPage(self.adapter),
            "orders": OrdersPage(self.adapter),
        }

        for page in self.pages.values():
            self.stack.addWidget(page)

        self.clients_btn = QPushButton("Clients")
        self.couriers_btn = QPushButton("Couriers")
        self.menu_btn = QPushButton("Menu")
        self.orders_btn = QPushButton("Orders")

        self.clients_btn.clicked.connect(lambda: self.show_page("clients"))
        self.couriers_btn.clicked.connect(lambda: self.show_page("couriers"))
        self.menu_btn.clicked.connect(lambda: self.show_page("menu"))
        self.orders_btn.clicked.connect(lambda: self.show_page("orders"))

        left_layout = QVBoxLayout()
        left_layout.addWidget(self.clients_btn)
        left_layout.addWidget(self.couriers_btn)
        left_layout.addWidget(self.menu_btn)
        left_layout.addWidget(self.orders_btn)
        left_layout.addStretch()

        left_panel = QWidget()
        left_panel.setLayout(left_layout)

        main_layout = QHBoxLayout()
        main_layout.addWidget(left_panel)
        main_layout.addWidget(self.stack, stretch=1)

        container = QWidget()
        container.setLayout(main_layout)
        self.setCentralWidget(container)

        self.show_page("clients")

    def show_page(self, name):
        self.stack.setCurrentWidget(self.pages[name])
