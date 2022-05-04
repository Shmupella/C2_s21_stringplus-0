Skip to content
Search or jump to…
Pull requests
Issues
Marketplace
Explore
 
@skysamurai 
Narzaru
/
string
Public
Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights
string/src/sprintf/sprintf.c
This commit does not belong to any branch on this repository, and may belong to a fork outside of the repository.
@Narzaru
Narzaru bgreydon/fix build
Latest commit 984cbbd on Dec 20, 2021
 History
 1 contributor
641 lines (574 sloc)  19.4 KB
   
#include "../s21_string.h"
#include <stdlib.h>

int s21_sprintf(char *str, char *format, ...) {
    va_list args;
    int bytes_written;
    va_start(args, format);
    bytes_written = s21_sprintf_(str, format, args);
    va_end(args);
    return bytes_written;
}

int s21_sprintf_(char *str, const char *format, va_list args) {
    format_info f_info;
    char *percent_pos;

    char *s_cursor = str;
    const char *f_cursor = format;

    while (f_cursor != S21_NULL) {
        // if the percent symbol is found,
        // copy the string until percent symbol
        // otherwise,
        // copy full string
        percent_pos = s21_strchr(f_cursor, '%');
        if (percent_pos != S21_NULL) {
            s21_memcpy(s_cursor, f_cursor,
                       sizeof(char) * (percent_pos - f_cursor));
            s_cursor += percent_pos - f_cursor;
            f_cursor += percent_pos - f_cursor + 1;
        } else {
            s21_memcpy(s_cursor, f_cursor, s21_strlen(f_cursor));
            s_cursor += s21_strlen(f_cursor);
            *s_cursor = '\0';
            f_cursor = S21_NULL;
        }

        if (f_cursor != S21_NULL && *f_cursor != '\0') {
            parse_format(&f_cursor, &f_info, args);

            if (*f_cursor == 'c') {
                put_char_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 's') {
                put_string_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'p') {
                put_pointer_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'n') {
                write_count_recorded_char(s_cursor - str, &f_info, args);
            } else if (*f_cursor == '%') {
                *s_cursor++ = '%';
            } else if (*f_cursor == 'o') {
                put_octo_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'X') {
                f_info.flags |= CAPITALIZE;
                put_hex_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'x') {
                put_hex_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'd' || *f_cursor == 'i') {
                f_info.flags |= SIGNED;
                put_dec_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'u') {
                put_udec_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'e') {
                put_exp_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'E') {
                f_info.flags |= CAPITALIZE;
                put_exp_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'g') {
                put_fortran_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'G') {
                f_info.flags |= CAPITALIZE;
                put_fortran_number_cursoring(&s_cursor, &f_info, args);
            } else if (*f_cursor == 'f') {
                put_flt_number_cursoring(&s_cursor, &f_info, args);
            }
            f_cursor++;
        }
    }
    return s_cursor - str;
}

void write_count_recorded_char(s21_size_t record_count, format_info *info,
                               va_list args) {
    void *number = va_arg(args, void *);
    if (info->qualifier == NONE) {
        *((int *)number) = (int)record_count;
    } else if (info->qualifier == SHORT) {
        *((short *)number) = (short)(record_count);
    } else if (info->qualifier == LONG) {
        *((long *)number) = (long)(record_count);
    }
}

int is_sign(char chr) { return chr == ' ' || chr == '+' || chr == '-'; }

void put_char_cursoring(char **str, format_info *info, va_list args) {
    if (!(info->flags & LEFT_JUSTIFY))
        while (--info->field_width > 0) *(*str)++ = ' ';
    *(*str)++ = va_arg(args, int);
    while (--info->field_width > 0) *(*str)++ = ' ';
}

void put_string_cursoring(char **str, format_info *info, va_list args) {
    const char *buf_string;
    int string_len;

    buf_string = va_arg(args, char *);

    if (!buf_string) buf_string = "(null)";

    string_len = s21_strlen(buf_string);
    if (info->precision != -1) {
        string_len = info->precision;
    }

    if (!(info->flags & LEFT_JUSTIFY)) {
        while (string_len < info->field_width--) {
            *(*str)++ = ' ';
        }
    }

    for (int i = 0; i < string_len; ++i) {
        *(*str)++ = *buf_string++;
    }

    while (string_len < info->field_width--) {
        *(*str)++ = ' ';
    }
}

void put_pointer_cursoring(char **str, format_info *info, va_list args) {
    info->number_system = 16;
    info->flags |= SPECIAL;
    info->flags |= UNSIGNED;
    info->qualifier = LONG;
    int_number_to_char(str, (long)va_arg(args, void *), info);
}

void put_hex_number_cursoring(char **str, format_info *info, va_list args) {
    info->number_system = 16;
    info->flags &= ~SIGNED;
    info->flags |= UNSIGNED;
    int_number_to_char(str, (long)va_arg(args, void *), info);
}

void put_dec_number_cursoring(char **str, format_info *info, va_list args) {
    info->number_system = 10;
    info->flags |= SIGNED;
    if (info->qualifier == NONE || info->qualifier == SHORT) {
        int_number_to_char(str, va_arg(args, int), info);
    } else if (info->qualifier == LONG) {
        int_number_to_char(str, va_arg(args, long), info);
    }
}

void put_udec_number_cursoring(char **str, format_info *info, va_list args) {
    info->number_system = 10;
    info->flags &= ~SIGNED;
    info->flags |= UNSIGNED;
    if (info->qualifier == NONE || info->qualifier == SHORT) {
        int_number_to_char(str, va_arg(args, int), info);
    } else if (info->qualifier == LONG) {
        int_number_to_char(str, va_arg(args, long), info);
    }
}

void put_octo_number_cursoring(char **str, format_info *info, va_list args) {
    info->flags &= ~SIGNED;
    info->flags |= UNSIGNED;
    info->number_system = 8;
    int_number_to_char(str, (long)va_arg(args, void *), info);
}

void put_fortran_number_cursoring(char **str, format_info *info, va_list args) {
    info->flags |= SIGNED;
    long double dlnumber;
    double dnumber;
    if (info->qualifier == LONG) {
        info->qualifier = FORTRAN_L;
        dlnumber = va_arg(args, long double);
        real_number_to_char(str, (void *)&dlnumber, info);
    } else {
        info->qualifier = FORTRAN;
        dnumber = va_arg(args, double);
        real_number_to_char(str, (void *)&dnumber, info);
    }
}

void put_exp_number_cursoring(char **str, format_info *info, va_list args) {
    info->flags |= SIGNED;
    info->flags |= EXPONENT;
    long double dlnumber;
    double dnumber;
    if (info->qualifier == LONG) {
        dlnumber = va_arg(args, long double);
        real_number_to_char(str, (void *)&dlnumber, info);
    } else if (info->qualifier == NONE) {
        dnumber = va_arg(args, double);
        real_number_to_char(str, (void *)(&(dnumber)), info);
    }
}

void put_flt_number_cursoring(char **str, format_info *info, va_list args) {
    info->flags |= SIGNED;
    info->flags |= EXPONENT;
    float snumber = va_arg(args, double);
    real_number_to_char(str, (void *)&snumber, info);
}

void int_number_to_char(char **str, unsigned long number, format_info *info) {
    char aggregate;
    char number_sign;
    char tmp[32];
    const char *digits_template;
    int i;

    // select the character output case
    if (info->flags & CAPITALIZE) {
        digits_template = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    } else {
        digits_template = "0123456789abcdefghijklmnopqrstuvwxyz";
    }

    // left alignment has a higher priority than zero padding
    if (info->flags & LEFT_JUSTIFY || info->precision > 0) {
        info->flags &= ~ZERO_PADDING;
    }

    if (info->flags & ZERO_PADDING) {
        aggregate = '0';
    } else {
        aggregate = ' ';
    }

    number_sign = '\0';
    if (info->flags & SIGNED) {
        if (info->qualifier == SHORT && ((short)number) < 0) {
            number = -(short)number;
            number_sign = '-';
            info->field_width--;
        } else if (info->qualifier == NONE && ((int)number) < 0) {
            number_sign = '-';
            info->field_width--;
            number = -(int)number;
        } else if (info->qualifier == LONG && ((long)number) < 0) {
            number_sign = '-';
            info->field_width--;
            number = -(long)number;
        } else if (info->flags & SHOW_SIGN) {
            number_sign = '+';
            info->field_width--;
        } else if (info->flags & SPACE_INSTEAD_SIGN) {
            number_sign = ' ';
            info->field_width--;
        }
    } else {
        if (info->qualifier == SHORT) {
            number = (unsigned short)number;
        } else if (info->qualifier == NONE) {
            number = (unsigned int)number;
        } else if (info->qualifier == LONG) {
            number = (unsigned long)number;
        }
        if (info->flags & SHOW_SIGN) {
            number_sign = '+';
            info->field_width--;
        }
    }

    // in the 16 number system
    // two characters are assigned to "0x",
    // in 8 number system to '0'
    if (info->flags & SPECIAL) {
        if (info->number_system == 16) {
            info->field_width -= 2;
        } else if (info->number_system == 8) {
            info->field_width -= 1;
        }
    }

    // put the number int the buffer
    i = 0;
    if (number == 0) {
        tmp[i++] = '0';
    } else {
        while (number != 0) {
            tmp[i++] = digits_template[number % info->number_system];
            number = number / info->number_system;
        }
    }

    if (i > info->precision) {
        info->precision = i;
    }
    info->field_width -= info->precision;

    if (!(info->flags & (ZERO_PADDING | LEFT_JUSTIFY))) {
        while (info->field_width-- > 0) {
            *(*str)++ = ' ';
        }
    }

    if (number_sign != '\0') {
        *(*str)++ = number_sign;
    }

    if (info->flags & SPECIAL) {
        if (info->number_system == 16) {
            *(*str)++ = '0';
            *(*str)++ = digits_template[33];
        } else if (info->number_system == 8) {
            *(*str)++ = '0';
        }
    }

    if (!(info->flags & LEFT_JUSTIFY)) {
        while (info->field_width-- > 0) {
            *(*str)++ = aggregate;
        }
    }

    while (i < info->precision--) {
        *(*str)++ = '0';
    }

    while (i-- > 0) {
        *(*str)++ = tmp[i];
    }

    while (info->field_width-- > 0) {
        *(*str)++ = ' ';
    }
}

void float_to_str(char *buffer, float number, format_info *info) {
    int number_sign;
    int exponent;
    char *number_digits;
    int isInf = 0;

    // i want to believe it works as it should word on Mac
    if (info->precision == 0) {
        number_digits =
            fcvt(number, info->precision + 1, &exponent, &number_sign);
        number_digits = ecvt(number, exponent, &exponent, &number_sign);
    } else {
        number_digits = fcvt(number, info->precision, &exponent, &number_sign);
    }

    if (number_digits != S21_NULL) {
        if (s21_strcmp(number_digits, "inf") == 0 ||
            s21_strcmp(number_digits, "-inf") == 0) {
            isInf = 1;
        }
    }

    // inserts number sign
    if (number_sign > 0) {
        *(buffer++) = '-';
    } else if (info->flags & SHOW_SIGN) {
        *(buffer++) = '+';
    } else if (info->flags & SPACE_INSTEAD_SIGN) {
        *(buffer++) = ' ';
    }
    // insert number dot if necessary
    if (exponent <= 0) {
        *(buffer++) = '0';
        if ((info->precision != 0 || info->flags & SPECIAL) && !isInf)
            *(buffer++) = '.';
        while (exponent++ < 0) {
            *(buffer++) = '0';
        }
    } else {
        while (exponent-- > 0) {
            *(buffer++) = *number_digits++;
        }
        if ((info->precision != 0 || info->flags & SPECIAL) && !isInf) {
            *(buffer++) = '.';
        }
    }
    while (*number_digits != '\0') {
        *(buffer++) = *number_digits++;
    }
}

void double_to_str(char *buffer, void *number, format_info *info) {
    int number_sign;
    int exponent;
    char *number_digits;
    char exponent_reverse[4];
    int i;
    int isInf = 0;

    if (info->qualifier == NONE) {
        number_digits = ecvt(*(double *)number, info->precision + 1, &exponent,
                             &number_sign);
    } else {
        number_digits = ecvt(*(long double *)number, info->precision + 1,
                             &exponent, &number_sign);
    }

    if (number_digits != S21_NULL) {
        if (s21_strcmp(number_digits, "inf") == 0 ||
            s21_strcmp(number_digits, "-inf") == 0) {
            isInf = 1;
        }
    }

    // insert number sign if necessary
    if (number_sign > 0) {
        *(buffer++) = '-';
    } else if (info->flags & SHOW_SIGN) {
        *(buffer++) = '+';
    } else if (info->flags & SPACE_INSTEAD_SIGN) {
        *(buffer++) = ' ';
    }

    // if (isInf)
    // printf("\nHERE: %d | %s\n", info->flags & SHOW_SIGN, number_digits);

    if (!isInf) {
        // output of a normalized number
        *(buffer++) = *number_digits++;

        // put dot after normalized number
        if ((info->flags & SPECIAL || info->precision != 0) && !isInf)
            *(buffer++) = '.';

        // mantiss output
        while ((info->precision)-- > 0) {
            *(buffer++) = *(number_digits++);
        }

        if (info->flags & CAPITALIZE) {
            *(buffer++) = 'E';
        } else {
            *(buffer++) = 'e';
        }

        // The exponent always has a sign,
        // so we don't have to equate it to zero
        if (exponent > 0) {
            *(buffer++) = '+';
            exponent -= 1;
        } else {
            *(buffer++) = '-';
            exponent = -exponent;
            exponent += 1;
        }

        if (exponent == 0) {
            *(buffer++) = '0';
            *(buffer++) = '0';
        } else {
            if (exponent <= 9) {
                *(buffer++) = '0';
            }
            for (i = 0; exponent > 0; ++i) {
                exponent_reverse[i] = '0' + exponent % 10;
                exponent /= 10;
            }
            while (i > 0) {
                *(buffer++) = exponent_reverse[(i--) - 1];
            }
        }
    } else {
        *(buffer++) = 'i';
        *(buffer++) = 'n';
        *(buffer++) = 'f';
    }
}

void double_to_fortran(char *buffer, void *number, format_info *info) {
    int i = 0;
    int j = 0;
    int exponent;
    // char exponent_sign;
    char *number_digits;
    // char *tmp = buffer;
    int number_sign;
    int isInf = 0;

    // calculating the exponent to select the output format
    if (info->qualifier == FORTRAN_L) {
        number_digits = ecvt(*(long double *)number, info->precision + 1,
                             &exponent, &number_sign);
        info->qualifier = LONG;
    } else {
        number_digits = ecvt(*(double *)number, info->precision + 1, &exponent,
                             &number_sign);
        info->qualifier = NONE;
    }

    if (number_digits != S21_NULL) {
        if (s21_strcmp(number_digits, "inf") == 0 ||
            s21_strcmp(number_digits, "-inf") == 0) {
            isInf = 1;
        }
    }
    if (!isInf) {
        // float
        if (info->precision == 0) {
            info->precision++;
        }
        if ((info->precision > (exponent - 1)) && (exponent - 1 >= -4)) {
            // ecvt does not work correctly with precision for float
            if (info->qualifier == LONG) {
                number_digits = ecvt(*(long double *)number, info->precision,
                                     &exponent, &number_sign);
            } else {
                number_digits = ecvt(*(double *)number, info->precision,
                                     &exponent, &number_sign);
            }
            j = s21_strlen(number_digits) - 1;
            if (!(info->flags & SPECIAL)) {
                while (number_digits[j] == '0' && j > 0 && j >= exponent) {
                    number_digits[j--] = '\0';
                }
                if (j == exponent - 1) {
                    info->precision = 0;
                }
            }
            // inserts number sign
            if (number_sign > 0) {
                *(buffer++) = '-';
            } else if (info->flags & SHOW_SIGN) {
                *(buffer++) = '+';
            } else if (info->flags & SPACE_INSTEAD_SIGN) {
                *(buffer++) = ' ';
            }
            // insert number dot if necessary
            if (exponent <= 0) {
                *(buffer++) = '0';
                if ((info->precision != 0 || info->flags & SPECIAL) && !isInf)
                    *(buffer++) = '.';
                while (exponent++ < 0) {
                    *(buffer++) = '0';
                }
            } else {
                while (exponent-- > 0) {
                    *(buffer++) = *number_digits++;
                }
                if ((info->precision != 0 || info->flags & SPECIAL) && !isInf) {
                    *(buffer++) = '.';
                }
            }
            while (*number_digits != '\0') {
                *(buffer++) = *number_digits++;
            }
            // double
        } else {
            info->precision--;
            double_to_str(buffer, number, info);
            if (!(info->flags & SPECIAL)) {
                while (buffer[j] != 'e' && buffer[j] != 'E') {
                    --j;
                }
                for (i = j - 1; i > 0 && buffer[i] == '0'; --i) {
                    buffer[i] = '\0';
                }
                if (buffer[i] == '.') {
                    buffer[i] = '\0';
                } else {
                    i += 1;
                }
                while (buffer[j] != '\0') {
                    buffer[i++] = buffer[j++];
                }
            }
        }
    } else {
        // inserts number sign
        if (number_sign > 0) {
            *(buffer++) = '-';
        } else if (info->flags & SHOW_SIGN) {
            *(buffer++) = '+';
        } else if (info->flags & SPACE_INSTEAD_SIGN) {
            *(buffer++) = ' ';
        }
        *(buffer++) = 'i';
        *(buffer++) = 'n';
        *(buffer++) = 'f';
    }
}

void real_number_to_char(char **str, void *number, format_info *info) {
    int i = 0;
    // char placeholder;

    if (info->precision == -1) {
        info->precision = 6;
    }

    char str_number[512] = {0};

    // processing numbers by type
    if (info->qualifier == NONE || info->qualifier == LONG) {
        double_to_str(str_number, number, info);
    } else if (info->qualifier == SHORT) {
        float_to_str(str_number, *((float *)number), info);
    } else if (info->qualifier == FORTRAN || info->qualifier == FORTRAN_L) {
        double_to_fortran(str_number, number, info);
    }

    info->field_width -= s21_strlen(str_number);

    if (info->flags & LEFT_JUSTIFY) {
        info->flags &= ~ZERO_PADDING;
    }

    if (info->flags & ZERO_PADDING) {
        if (!(s21_strcmp(str_number, "inf") == 0 ||
              s21_strcmp(str_number, "+inf") == 0 ||
              s21_strcmp(str_number, "-inf") == 0)) {
            if (is_sign(str_number[i])) {
                *(*str)++ = str_number[i++];
            }
            while (info->field_width-- > 0) {
                *(*str)++ = '0';
            }
        } else {
            while (info->field_width-- > 0) {
                *(*str)++ = ' ';
            }
        }
    }

    if (!(info->flags & LEFT_JUSTIFY)) {
        while (info->field_width-- > 0) {
            *(*str)++ = ' ';
        }
    }

    while (str_number[i] != '\0') {
        *(*str)++ = str_number[i++];
    }

    while (info->field_width-- > 0) {
        *(*str)++ = ' ';
    }
}
© 2022 GitHub, Inc.
Terms
Privacy
Security
Status
Docs
Contact GitHub
Pricing
API
Training
Blog
About
Loading complete