const express = require('express');
const axios = require('axios');

const app = express();

app.get('/start', (req, res) => {
  res.send("To authorize click <a href=\"https://vz271109.eurodir.ru/oauth/authorize/?client_id=local.5d8e18b02ecd04.99678525&state=helloworld\">here</a>");
});

app.get('/', async (req, res) => {
  const code = req.query.code;
  const state = req.query.state;

  const response = await axios.default.get(`https://oauth.bitrix.info/oauth/token/?grant_type=authorization_code&client_id=local.5d8e18b02ecd04.99678525&client_secret=OboiffOkf5tu8q3rNIosiQTxmG4xCE8aI8jWIHbBltITj0Np1k&code=${code}`);

  const token = response.data.access_token;

  const result = await axios.default.post('https://vz271109.eurodir.ru/rest/log.blogpost.add.json', {
    auth: token,
    POST_MESSAGE: "Hello world"
  });
  res.send();
});

app.listen(3000);