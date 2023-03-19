import React from 'react';
import ReactDOM from 'react-dom';
import { Provider } from 'react-redux';
import { Auth0Provider } from '@auth0/auth0-react';
import store from './store';
import App from './App';
import './styles/index.css';

ReactDOM.render(
  <React.StrictMode>
    <Auth0Provider
      domain="dev-yrdnvh536r2143k8.us.auth0.com"
      clientId="UBZZ7ZrzGjLb28JFe5B9gbzqjnfVBvjH"
      redirectUri={window.location.origin}
    >
      <Provider store={store}>
        <App />
      </Provider>
    </Auth0Provider>
  </React.StrictMode>,
  document.getElementById('root')
);

