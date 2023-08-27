import dash
from dash import Dash, dcc, html, Input, Output
import dash_bootstrap_components as dbc

app = Dash(__name__, use_pages=True,external_stylesheets=[dbc.themes.BOOTSTRAP])


pages = ["Home","Table"]

app.layout = html.Div([
    html.Div(
	    html.H1(children='Banking DashBoard', className="header-title"),
        className="page-top"
    ),

    html.Div(
        [
            html.Div(
                dcc.Link(
                    pages[0], href="/", className="nav-link"
                ),
                className="nav-bar"
            ),
            html.Div(
                dcc.Link(
                    pages[1], href="/Table", className="nav-link"
                ),
                className="nav-bar"
            ),
        ], 
        className="nav-top"
    ),
	dash.page_container
] )

if __name__ == '__main__':
	app.run_server(host= '0.0.0.0',debug=True)