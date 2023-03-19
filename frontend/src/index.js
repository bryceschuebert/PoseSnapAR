import React from 'react';
import ReactDOM from 'react-dom';
import { BrowserRouter } from 'react-router-dom';
import { Auth0ProviderWithNavigate } from "./auth0-provider-with-navigate";
import App from './App';
import './index.css';

ReactDOM.render(
  <React.StrictMode>
    <BrowserRouter>
      <Auth0ProviderWithNavigate>
        <App />
      </Auth0ProviderWithNavigate>
    </BrowserRouter>
  </React.StrictMode>,
  document.getElementById('root')
);


