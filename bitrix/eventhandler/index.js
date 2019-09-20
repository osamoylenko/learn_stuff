const express = require('express');
const bodyParser = require('body-parser');
const axios = require('axios');

const app = express();

app.post('/event', bodyParser.urlencoded(), (req, res) => {
  const taskId = req.body.data.FIELDS_AFTER.ID;
  const restURL = req.body.auth.client_endpoint + 'tasks.task.get.json';

  axios.default.post(restURL, {
    auth: req.body.auth.access_token,
    taskId: taskId,
    select: ['TITLE']
  }).then(r => { 
    console.log(`Имя созданной задачи ${r.data.result.task.title}`);
  })
  .catch(e => console.log(e));
});

app.listen(5000);