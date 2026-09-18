// Forwards the game's Jev request (built in C++, src/Jev.cpp) to Vercel AI Gateway with the
// server's AI_GATEWAY_API_KEY. The model and endpoint are fixed here, so the key can't be used
// for other models through this route. Set a spend limit in Vercel for the rest.
export async function POST(request) {
  const body = await request.text();
  if (body.length > 65536) {
    return new Response('{"error":"too large"}', { status: 413 });
  }
  const res = await fetch('https://ai-gateway.vercel.sh/v4/ai/evaluation-model', {
    method: 'POST',
    headers: {
      'Authorization': `Bearer ${process.env.AI_GATEWAY_API_KEY}`,
      'Content-Type': 'application/json',
      'Ai-Gateway-Protocol-Version': '0.0.1',
      'Ai-Gateway-Auth-Method': 'api-key',
      'Ai-Evaluation-Model-Specification-Version': '4',
      'Ai-Model-Id': 'typesafe-ai/jev',
    },
    body,
    signal: AbortSignal.timeout(8000),
  });
  return new Response(await res.text(), { status: res.status, headers: { 'Content-Type': 'application/json' } });
}
