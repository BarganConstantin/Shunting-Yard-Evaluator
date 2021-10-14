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
        }
        function clearLast()
        {           
            let str= document.form.textview.value;
            let newStr = str.substring(0, str.length - 1);
            document.form.textview.value = newStr;
        }