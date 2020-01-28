import React from 'react'
import Icon from 'react-native-vector-icons/MaterialIcons'

import styles from './styles'

import { TouchableOpacity, Text } from 'react-native'
 
 
export default function CheckBox(props) {
    const {
        selected,                      // Optional, no label if labelText is undefined
        onPress,                     // styles for label
        style,                     // styles for Input
        textStyle,                    // Additional props for input
        size = 30,
        color = '#211f30', text = '',
        
    } = props;
    return (
        <TouchableOpacity style={[styles.checkBox, style]} onPress={onPress} {...props}>
        <Icon
            size={size}
            color={color}
            name={ selected ? 'check-box' : 'check-box-outline-blank'}
        />

        <Text style={textStyle}> {text} </Text>
    </TouchableOpacity>
    );
}

 
