import React from 'react';
import { Button } from 'antd';
import styles from './button.module.css';

const OpenProjectButton = ({ onClick }) => {
  return (
    <Button
      type="link"
      onClick={onClick}
      className={styles.navText}
    >
      Open
    </Button>
  );
};

export default OpenProjectButton;