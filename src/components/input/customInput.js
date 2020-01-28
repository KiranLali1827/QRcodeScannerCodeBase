import React from 'react';
import { StyleSheet } from 'react-native';
import { Input, Item, Label } from 'native-base';

export default function CustomInput(props) {
    const {
        labelText,                      // Optional, no label if labelText is undefined
        inputStyle,                     // styles for label
        labelStyle,                     // styles for Input
        inputProps,                     // Additional props for input
        value,
        disabled,
        autofocus,
        autoCapitalize,
        onChange,
        keyboardType,                   // type of keyboard to open
        maxLength,                       // maximum length of chars allowed
        placeholder
    } = props;
    return (
        <Item floatingLabel={!!labelText} style={styles.root}>
            {labelText && <Label style={labelStyle}>{labelText}</Label>}
            <Input
                editable={true}
                value={value}
                autoFocus={!!autofocus}
                onChangeText={onChange}
                style={inputStyle}
                editable={!disabled}
                {...{ autoCapitalize, keyboardType, maxLength, placeholder }}
                {...inputProps}
            />
        </Item>
    );
}


const styles = StyleSheet.create({
    root: {
        marginTop: 10
    }
});
