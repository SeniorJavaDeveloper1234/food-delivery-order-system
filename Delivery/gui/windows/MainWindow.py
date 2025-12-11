

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

        self.apply_dark_theme()
        self.showMaximized()

        self.show_page("clients")

        
    def show_page(self, name):
        self.stack.setCurrentWidget(self.pages[name])


    def apply_dark_theme(self):
        self.setStyleSheet("""
QWidget {
    background-color: #1E1E1E;
    color: #F0F0F0;
    font-size: 14px;
}

QPushButton {
    background-color: #2D2D30;
    border: 1px solid #3A3A3D;
    border-radius: 6px;
    padding: 6px 12px;
    color: #F0F0F0;
}
QPushButton:hover {
    background-color: #3D3D40;
}
QPushButton:pressed {
    background-color: #5A5A5D;
}

QLineEdit, 
QComboBox {
    background-color: #2D2D30;
    border: 1px solid #3A3A3D;
    padding: 6px;
    border-radius: 4px;
    color: #FFFFFF;
}

QComboBox QAbstractItemView {
    background-color: #2D2D30;
    color: #FFFFFF;
    selection-background-color: #444444;
}

QTableWidget {
    background-color: #252526;
    gridline-color: #3A3A3D;
    border: 1px solid #3A3A3D;
    color: #F0F0F0;
}

QHeaderView::section {
    background-color: #2D2D30;
    color: #FFFFFF;
    padding: 6px;
    border: none;
    border-right: 1px solid #3A3A3D;
}

QTableWidget::item:selected {
    background-color: #444444;   
    color: #FFFFFF;
}

QTableWidget::item:hover {
    background-color: #333333;
}

QScrollBar:vertical {
    background: #2D2D30;
    width: 12px;
}
QScrollBar::handle:vertical {
    background: #4A4A4D;
    border-radius: 4px;
}
QScrollBar::handle:vertical:hover {
    background: #6A6A6D;
}

QScrollBar:horizontal {
    background: #2D2D30;
    height: 12px;
}
QScrollBar::handle:horizontal {
    background: #4A4A4D;
    border-radius: 4px;
}
QScrollBar::handle:horizontal:hover {
    background: #6A6A6D;
}

""")
