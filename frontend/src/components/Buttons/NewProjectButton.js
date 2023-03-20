import React from 'react';
import { Button } from 'antd';
import styles from './button.module.css';

const NewProjectButton = ({ onClick }) => {
  return (
    <Button
      type="link"
      onClick={onClick}
      className={styles.navText}
    >
      New
    </Button>
  );
};

export default NewProjectButton;
