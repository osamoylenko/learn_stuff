const express = require('express');
const bodyParser = require('body-parser');
const axios = require('axios');

const app = express();

app.post('/', bodyParser.urlencoded(), (req, res) => {
  const authID = req.body.AUTH_ID;
  const restURL = "https://vz271109.eurodir.ru/rest/tasks.task.add.json";

  axios.default.post(restURL, {
    auth: authID,
    fields: {
      TITLE: 'TASK NAME',
      RESPONSIBLE_ID: '1'
    }
  }).then(r => { 
    console.log(r.data);
    res.send(r.data);
  })
  .catch(e => console.log(e));
});

app.listen(8000)