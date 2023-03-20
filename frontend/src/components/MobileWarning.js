import React from 'react';
import { Typography } from 'antd';

const { Text } = Typography;

const MobileWarning = () => {
  const isMobile = window.innerWidth <= 768;

  return (
    isMobile && (
      <div style={{ display: 'flex', justifyContent: 'center', alignItems: 'center', height: '100vh' }}>
        <Text style={{ fontSize: '24px' }}>
          Please use a desktop screen for the best experience.
        </Text>
      </div>
    )
  );
};

export default MobileWarning;

