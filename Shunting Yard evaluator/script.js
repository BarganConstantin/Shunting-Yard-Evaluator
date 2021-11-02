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
            alert("Expresia introdusa = " + str);
            document.form.textview.value = "";
            input_expresion = str;

            solve_expresion();
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
                let tmpToken = new String();
                if (input_expresion[i].charCodeAt(0) > 47 && input_expresion[i].charCodeAt(0) < 58)
                {
                    while (input_expresion[i].charCodeAt(0) > 47 && input_expresion[i].charCodeAt(0) < 58)
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
            debugger;
            let token_size = 0;
            i = 0;
            while (token[i] != undefined)
            {
                token_size++;
                i++;
            }
            for (i = 0; i < token_size; i++)
            {
                alert(token[i]);
            }
        }

        function solve_expresion()
        {
            make_token();
        }

        