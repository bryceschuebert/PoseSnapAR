import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import './styles/login.css';

const Login = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');

  const handleSubmit = (e) => {
    e.preventDefault();
    // Call login API here
  };

  return (
    <div>
      <h1>Welcome to PoseSnapAR</h1>
      <h2>Login</h2>
      <button>Login with Google</button>
      <button>Login with Facebook</button>
      <button>Login with Apple</button>
      <h3>Or</h3>
      <form onSubmit={handleSubmit}>
        <div>
          <label>Email:</label>
          <input type="email" value={email} onChange={(e) => setEmail(e.target.value)} required />
        </div>
        <div>
          <label>Password:</label>
          <input type="password" value={password} onChange={(e) => setPassword(e.target.value)} required />
        </div>
        <button type="submit">Login</button>
      </form>
      <p>
        Don't have an account? <Link to="/register">Create one</Link>
      </p>
    </div>
  );
};

export default Login;


