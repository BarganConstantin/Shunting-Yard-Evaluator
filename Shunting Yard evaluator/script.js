        let input_expresion = new String();
        function insert(num)
        {
            document.form.textview.value = document.form.textview.value + num;
        }
        function deleteinput()
        {
            document.form.textview.value = "";
        }
        function result()
        {
            let str = document.form.textview.value;
            //alert("Expresia introdusa = " + str);
            document.form.textview.value = "";
            input_expresion = str;

            document.form.textview.value = solve_expresion();
        }
        function clearLast()
        {           
            let str= document.form.textview.value;
            let newStr = str.substring(0, str.length - 1);
            document.form.textview.value = newStr;
        }

        let elem_num;
        let token;

        function make_token()
        {
            elem_num = input_expresion.length;
            token = new Array(elem_num - 1);
            let token_index = 0;
            let i = 0;
            while (i < elem_num)
            {
                let tmpToken = new String();debugger;
                if (input_expresion[i].charCodeAt(0) > 47 && input_expresion[i].charCodeAt(0) < 58 || i == 0 && input_expresion[i] == "-" || i != 0 && input_expresion[i - 1].charCodeAt(0) == 40 && input_expresion[i] == "-")
                {
                    while (input_expresion[i].charCodeAt(0) > 47 && input_expresion[i].charCodeAt(0) < 58 || input_expresion[i].charCodeAt(0) == 46 || input_expresion[i] == "-" && i == 0 || input_expresion[i - 1].charCodeAt(0) == 40 && input_expresion[i] == "-")
                    {
                        tmpToken = tmpToken + input_expresion[i];
                        i++; 
                        if (i == elem_num) break;
                    }
                }
                else
                {
                    tmpToken = input_expresion[i];
                    i++;
                }
                
                token[token_index] = tmpToken;
                token_index++;
                if (i == elem_num) break;
            }
            let token_size = 0;
            i = 0;
            while (token[i] != undefined)
            {
                token_size++;
                i++;
            }
            elem_num = token_size;
        }
        
        function get_precedence(operation)
        {
            switch (operation)
            {
                case "(":
                    return 0;
                case "+":
                    return 2;
                case "-":
                    return 2;
                case "*":
                    return 3;
                case "/":
                    return 3;
                case "√":
                    return 4;
            }
        }

        function make_operation(a, b, operation)
        {
            switch (operation)
            {
                case "+":
                    return a + b;
                case "-":
                    return a - b;
                case "*":
                    return a * b;
                case "/":
                    return a / b;
                case "√":
                    return newton(a);
            }
        }

        let final_result;

        function solve_expresion()
        {
            make_token();debugger;
            let num_stack = [];
            let operation_queue = [];
            debugger;
            for (let i = 0; i < elem_num; i++)
            {
                tmpToken = token.shift();
                if (tmpToken[0].charCodeAt(0) > 47 && tmpToken[0].charCodeAt(0) < 58 || tmpToken[0] == "-" && tmpToken[1] != undefined)
                {
                    let num = parseFloat(tmpToken);
                    num_stack.push(num);
                }
                else if (tmpToken[0].charCodeAt(0) == 40)   // (
                {
                    operation_queue.push(tmpToken);
                }
                else if (tmpToken[0].charCodeAt(0) == 41)   // )
                {
                    while (true)
                    {
                        let tmp_operation = operation_queue.pop();
                        if (tmp_operation[0].charCodeAt(0) == 40)
                        {
                            break;
                        }
                        else
                        {
                            let a = num_stack.pop();
                            let b = num_stack.pop();
                            let tmp_result = make_operation(b, a, tmp_operation);

                            num_stack.push(tmp_result);
                        }
                    }
                }
                else
                {
                    if (operation_queue.length == 0)
                    {
                        operation_queue.push(tmpToken);
                    }
                    else
                    {
                        let current_precedence = get_precedence(tmpToken);
                        let last_operation_stack = operation_queue.pop();
                        let last_precedence = get_precedence(last_operation_stack);
                        if (current_precedence > last_precedence)
                        {
                            operation_queue.push(last_operation_stack);
                            operation_queue.push(tmpToken);
                        }
                        else
                        {
                            while (last_precedence >= current_precedence)
                            {
                                let a;
                                let b;
                                let tmp_result;
                                if (last_operation_stack == "√")
                                {
                                    a = num_stack.pop();
                                    tmp_result = make_operation(a, 0, last_operation_stack);
                                }
                                else
                                {
                                    a = num_stack.pop();
                                    b = num_stack.pop();
                                    tmp_result = make_operation(b, a, last_operation_stack);
                                }

                                num_stack.push(tmp_result);

                                last_operation_stack = operation_queue.pop();
                                if (last_operation_stack == undefined)
                                {
                                    break;
                                }
                                else
                                {
                                    last_precedence = get_precedence(last_operation_stack);
                                }
                            }
                            if (last_operation_stack != undefined) operation_queue.push(last_operation_stack);
                            operation_queue.push(tmpToken);
                        }
                    }
                } 
            }
            
            //calculate final result
            let operation = operation_queue.pop();
            if (operation == undefined)
            {
                final_result = num_stack[0];
                return final_result;
            }
            while (operation != undefined)
            {
                let a;
                let b;
                let tmp_result;
                if (operation == "√")
                {
                    a = num_stack.pop();
                    tmp_result = make_operation(a, 0, operation);
                }
                else
                {
                    a = num_stack.pop();
                    b = num_stack.pop();
                    tmp_result = make_operation(b, a, operation);
                }
                num_stack.push(tmp_result);
                operation = operation_queue.pop();
            }
            final_result = num_stack[0];
            return final_result;
        }

function newton(a)
{
    let x = 1;
    let x_last;
    let c = 1;

    while (c > 0.0005)
    {
        x_last = 0.5 * (x + (a / x));
        c = Math.abs(x_last - x);
        x = x_last;
    }

    return x_last.toFixed(4);
}